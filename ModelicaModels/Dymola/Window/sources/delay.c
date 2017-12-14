/*
 * Copyright (C) 1995-2001 Dynasim AB.
 * All rights reserved.
 *
 */

/* delay.c

   first implementation:
         Dieter Moormann (DLR), till Nov 14, 1995
   variable delays introduced:
         Dieter Moormann (DLR),      Apr 29, 1996  
   derivatives introduced:
         Dieter Moormann (DLR),      May 29, 1996  
   simplifications of code:
         Hilding Elmqvist,           December 16, 1996  
   increased maxid from 100 to 500:
         Hilding Elmqvist,           April 17, 1997 
   
   new functions for Delay & Derivatives added
   for Dymola version 3.1:
         Dieter Moormann (DLR)       April, 4, 1998

*/

/* DLL-status: Lot of static data used/defined in file => turned into TLS */

#if !defined(NO_FILE)
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dymutil.h"
#include "delay.h"
#include "dlldata.h"

#if 0
#define MAX_DELAY 2000       /* maximum number of delays */
#define MAX_DERIVATIVE 2000  /* maximum number of true derivatives */

static delayStruct del[MAX_DELAY]; 
                               /* all delays are stored in this struct;
                                  each del contains all information of one delay or
                                  drivative */
static delayStruct deri[MAX_DERIVATIVE]; 
                               /* all derivatives are stored in this struct;
                                  each del contains all information of one delay or
                                  drivative */

static int lastDelayID = -1; /* whenever <delayinit> is called,
                               lastDelayID is increased by 1. */    

static int lastDerID = -1;   /* whenever <derinit> is called,
                               lastDerID is increased by 1. */  
#endif

/****************************************************************************************
 the following definitions are required for the Block library of
 Dymola version 3.0 or older.
 ****************************************************************************************/
#define maxid 1000         

#if 0
  static int oldid  = 0; /* whenever <delayinit> is called,
                            oldid is increased by 1. It returns the pointer
                            of the current id */
  static int delays = 0; /* counter for delays */
  static int init   = 1; /* init = 1: if <delayinit> is called, the
                                      initialization is done
                            init = 0: if <delayinit> is called, the
                                      initialization is not done

                            The switch <init> is set to 1 at the first call
                            of delay and at the end of each simulation
                            <delayclose>
                            The switch <init> is set to 0 by the function
                            <delayiniclos>, which is called at the end of
                            <dsblockS>.*/
#endif
/****************************************************************************************
 the   above   definitions are required for the Block library of
 Dymola version 3.0 or older.
 ****************************************************************************************/
  
DYMOLA_STATIC double delayIni(double delaytime, double buffer, double startTime, double u)
   {
      int buffersize = (int) (buffer + 0.1); 
                                     /* buffersize for storage allocation */
      char mess[500];
      int delayID;
	  struct DymosimSimulator*dymosimData;

	 dymosimData= dymosimGetThreadData();
   
      if (dymosimData->lastDelayID >= MAX_DELAY-1) {
         sprintf(mess,"The maximum number of delays (= %d) is reached.\n"
                "No more delay memory is available\n", (int) MAX_DELAY);
         DymosimError(mess);
      }
      ++ dymosimData->lastDelayID;
      delayID = dymosimData->lastDelayID;
   
   
      dymosimData->del[delayID].nx = buffersize;
      dymosimData->del[delayID].timedelay = delaytime;
      dymosimData->del[delayID].x  = (double *) malloc( sizeof (double) * buffersize * 2);
	  if (!dymosimData->del[delayID].x) {
		  sprintf(mess,"Failed to allocate memory for delay.\n You might decrease the number of delays\n "
			  " or the 'double Buffersize=%d;' in dymola/source/dsblock5.c\n",buffersize);
		  DymosimError(mess);
	  }
      dymosimData->del[delayID].y  = dymosimData->del[delayID].x + buffersize;

      dymosimData->del[delayID].x[0] = startTime - fabs(delaytime) - 1.0e6; 
                                  /* the first time value of the buffer x[0] is
                                     the starTime minus the absolute value 
                                     of the delaytime. To make sure that
                                     x[0] is smaller than x[1] even for delaytimes
                                     of zero, an additional an additional 1.0 is 
                                     substracted from x[0]. */
      dymosimData->del[delayID].x[1] = startTime;           
   
      dymosimData->del[delayID].y[0] = u;              /* <u>,here the inital u               */
      dymosimData->del[delayID].y[1] = u;              /* Extrapolation backwards will give constant u. */
      dymosimData->del[delayID].first = 0;             
      dymosimData->del[delayID].add = 1;               /* at this position the last element
                                          was placed */
      dymosimData->del[delayID].old = 1;               /* set initial interpolation position;
                                             at this value <delayget> will start
                                             finding the upper and lower bounds  */
   
      return delayID;
}

DYMOLA_STATIC int transportIni(double buffer, double startX, double u) {
	int delayID=(int)(delayIni(1,buffer,startX+1,u));
	int i;
	int initSize=((int )(buffer+0.1))/10;
	struct DymosimSimulator*dymosimData;
	dymosimData= dymosimGetThreadData();
#if 0
	for(i=0;i<(int)(buffer+0.1);++i) dymosimData->del[delayID].y[i]=dymosimData->del[delayID].x[i]=1e300;
#endif
	dymosimData->del[delayID].x[0]=startX;
	dymosimData->del[delayID].x[1]=startX+1e-9;

	for(i=0;i<initSize;++i)
		dymosimData->del[delayID].x[2+i]=startX+(i+0.5)/(initSize);
	dymosimData->del[delayID].x[initSize+2]=startX+1-1e-9;
	dymosimData->del[delayID].x[initSize+3]=startX+1;
	for(i=0;i<initSize+4;++i) dymosimData->del[delayID].y[i]=u;
	dymosimData->del[delayID].add=initSize+3;
	return delayID;
}

static double getXTransport(struct DymosimSimulator*dymosimData,int id,int num) {
#if 0
	if (del[id].x[num]>=1e100) {
		char str[100];
		sprintf(str,"Get %d => %g",num,del[id].x[num]);
		DymosimError(str);
	}
#endif
	if (!dymosimData) return 1e100; /* Error */
	return dymosimData->del[id].x[num];
}

DYMOLA_STATIC void transportGet(double T1,double T2,double x,int vs,int id,double*Tf1,double*Tf2) {
	double idd=id;
	struct DymosimSimulator*dymosimData;
	dymosimData= dymosimGetThreadData();

#if 0
	static const double neguno=-0.99999999999999;
	static const double uno=0.999999999999999;
	double xp1=x+1;
	if (!vs) {
		*Tf1=delayRead(&idd,&uno,&xp1);
		*Tf2=T2;
	} else {
		*Tf1=T1;
		*Tf2=delayRead(&idd,&neguno,&x);
	}
#else
	if (dymosimData->del[id].x==0) {
		*Tf1=T1;
		*Tf2=T2;
		return;
	}
	if (!vs) {
		int old=dymosimData->del[id].old;
		while(getXTransport(dymosimData,id,old)<=x && old!=dymosimData->del[id].add) {
			int oldnext=old+1;
			if (oldnext>=dymosimData->del[id].nx) oldnext=0;
#if 0
			{
				char str[200];
				sprintf(str,"Up %g %g %g",x,dymosimData->del[id].x[old],dymosimData->del[id].x[oldnext]);
				DymosimMessage(str);
			}
#endif
			old=oldnext;
		}

		for(;;) {
			int oldpre=old-1;
			if (oldpre<0) oldpre=dymosimData->del[id].nx-1;
			if (oldpre==dymosimData->del[id].first) break;
			if (dymosimData->del[id].x[oldpre]<x) break;
#if 0
			{
				char str[200];
				sprintf(str,"Down %g %g %g",x,dymosimData->del[id].x[oldpre],dymosimData->del[id].x[old]);
				DymosimMessage(str);
			}
#endif
			old=oldpre;
		}
		/* Post: dymosimData->del[id].x[oldpre]<=x<dymosimData->del[id].x[old], or at bounds */
		dymosimData->del[id].old=old;
		*Tf2=T2;
		{
			int oldpre=(old==0)?(dymosimData->del[id].nx-1):(old-1);
			double x0=getXTransport(dymosimData,id,oldpre);
			double x1=getXTransport(dymosimData,id,old);
			double y0=dymosimData->del[id].y[oldpre];
			double y1=dymosimData->del[id].y[old];
#if 0
			if (!(x0<=x && x<x1)) {
				char str[200];
				sprintf(str,"Ooops2: %d %g %g %g %g %g %d %d %d %d",id,x,x0,x1,y0,y1,oldpre,old,dymosimData->del[id].first,dymosimData->del[id].add);
				DymosimMessage(str);
			}
#endif
			if (x<=x0)
				*Tf1=y0;
			else if (x>=x1)
				*Tf1=y1;
			else
				*Tf1=y0+(y1-y0)*((x)-x0)/(x1-x0);
		}
	} else {
		int old=dymosimData->del[id].old;
		while(getXTransport(dymosimData,id,old)<x+1 && old!=dymosimData->del[id].add) {
			int oldnext=old+1;
			if (oldnext>=dymosimData->del[id].nx) oldnext=0;
			old=oldnext;
		}

		for(;;) {
			int oldpre=old-1;
			if (oldpre<0) oldpre=dymosimData->del[id].nx-1;
			if (oldpre==dymosimData->del[id].first) break;
			if (dymosimData->del[id].x[oldpre]<=x+1) break;
			old=oldpre;
		}
		/* Post: dymosimData->del[id].x[oldpre]<x<=dymosimData->del[id].x[old], or at bounds */
		*Tf1=T1;
		dymosimData->del[id].old=old;
		{
			int oldpre=(old==0)?(dymosimData->del[id].nx-1):(old-1);
			double x0=getXTransport(dymosimData,id,oldpre);
			double x1=getXTransport(dymosimData,id,old);
			double y0=dymosimData->del[id].y[oldpre];
			double y1=dymosimData->del[id].y[old];
#if 0
			if (!(x0<=x+1 && x+1<x1)) {
				char str[200];
				sprintf(str,"Ooops: %d %.17g %.17g %.17g %g %g",id,x,x0,x1,y0,y1);
				DymosimMessage(str);
			}
#endif
			if (x+1<=x0)
				*Tf2=y0;
			else if (x+1>=x1)
				*Tf2=y1;
			else
				*Tf2=y0+(y1-y0)*((x+1)-x0)/(x1-x0);
		}
	}
#endif
}


DYMOLA_STATIC void transportPut(double T1,double T2,double x,int vs,int id) {
	struct DymosimSimulator*dymosimData;
	dymosimData= dymosimGetThreadData();
	if (dymosimData->del[id].x==0) return; 
	if (!vs) {
		/* Add T2 at x+1 as last value */
		int add=dymosimData->del[id].add;
		int preadd=add-1;
		if (preadd<0) preadd=dymosimData->del[id].nx-1;
		if (getXTransport(dymosimData,id,add)==x+1)
			; /* No need to add it */
		else if (getXTransport(dymosimData,id,add)<=x+1 && fabs(getXTransport(dymosimData,id,preadd)-(x+1))>=0.7/dymosimData->del[id].nx) {
			++add;
			if (add>=dymosimData->del[id].nx)
				add=0;
			if (add==dymosimData->del[id].first) {
				int newfirst=dymosimData->del[id].first;
				newfirst++;
				if (newfirst>=dymosimData->del[id].nx) newfirst=0;
				if (dymosimData->del[id].old==dymosimData->del[id].first) dymosimData->del[id].old=newfirst;
				dymosimData->del[id].first=newfirst;
			}
		} else {
			while(add!=dymosimData->del[id].first && getXTransport(dymosimData,id,preadd)>x+1) {
#if 0
				{
					char str[200];
					sprintf(str,"Removing value2 %g %g %g",x,dymosimData->del[id].x[add],dymosimData->del[id].x[preadd]);
					DymosimMessage(str);
					del[id].x[add]=1e300;
				}
#endif
				if (dymosimData->del[id].old==add)
					dymosimData->del[id].old=preadd;
				add=preadd;
				preadd=add-1;
				if (preadd<0) preadd=dymosimData->del[id].nx-1;
			}
		}
		dymosimData->del[id].add=add;
		dymosimData->del[id].x[add]=x+1;
		dymosimData->del[id].y[add]=T2;
	} else {
		/* Add T1 at x as first value */
		int first=dymosimData->del[id].first;
		int postfirst=first+1;
		if (postfirst>=dymosimData->del[id].nx) postfirst=0;
		if (getXTransport(dymosimData,id,first)==x)
			; /* No need to add it */
		else if (getXTransport(dymosimData,id,first)>=x && fabs(getXTransport(dymosimData,id,postfirst)-x)>=0.7/dymosimData->del[id].nx) {
			--first;
			if (first<0)
				first=dymosimData->del[id].nx-1;
			if (first==dymosimData->del[id].add) {
				int newadd=dymosimData->del[id].add;
				newadd--;
				if (newadd<0) newadd=dymosimData->del[id].nx-1;
				if (dymosimData->del[id].old==dymosimData->del[id].add) dymosimData->del[id].old=newadd;
				dymosimData->del[id].add=newadd;
			}
		} else {
			while(first!=dymosimData->del[id].add && getXTransport(dymosimData,id,postfirst)<x) {
#if 0
				{
					char str[200];
					sprintf(str,"Removing value %g %g %g",x,dymosimData->del[id].x[first],dymosimData->del[id].x[postfirst]);
					DymosimMessage(str);
					del[id].x[first]=1e300;
				}
#endif
				if (dymosimData->del[id].old==first)
					dymosimData->del[id].old=postfirst;
				first=postfirst;
				postfirst=first+1;
				if (postfirst>=dymosimData->del[id].nx) postfirst=0;
			}
		}
		dymosimData->del[id].first=first;
		dymosimData->del[id].x[first]=x;
		dymosimData->del[id].y[first]=T1;
	}
}
DYMOLA_STATIC void transportFunction(double T1,double T2,double x,int vs,int id,double*Tf1,double*Tf2) {
#if 0
	DymosimMessageDouble("x:",x);
	DymosimMessageInt("vs:",vs);
	DymosimMessageInt("x add",dymosimData->del[id].add);
	DymosimMessageInt("x first",dymosimData->del[id].first);
	DymosimMessageDouble("x 0 in table",dymosimData->del[id].x[0]);
	DymosimMessageDouble("x 1 in table",dymosimData->del[id].x[1]);
#endif
	transportPut(T1,T2,x,vs,id);
	transportGet(T1,T2,x,vs,id,Tf1,Tf2);
#if 0
	DymosimMessageInt("x add",dymosimData->del[id].add);
	DymosimMessageInt("x first",dymosimData->del[id].first);

	DymosimMessageDouble("x add in table",dymosimData->del[id].x[dymosimData->del[id].add]);
	DymosimMessageDouble("y add in table",dymosimData->del[id].y[dymosimData->del[id].add]);
	DymosimMessageDouble("x first in table",dymosimData->del[id].x[dymosimData->del[id].first]);
	DymosimMessageDouble("y first in table",dymosimData->del[id].y[dymosimData->del[id].first]);
	DymosimMessageDouble("x 0 in table",dymosimData->del[id].x[0]);
	DymosimMessageDouble("y 0 in table",dymosimData->del[id].y[0]);
	DymosimMessageDouble("x 1 in table",dymosimData->del[id].x[1]);
	DymosimMessageDouble("y 1 in table",dymosimData->del[id].y[1]);
#endif

#if 0
	DymosimMessageDouble("Tf1:",*Tf1);
	DymosimMessageDouble("Tf2:",*Tf2);
#endif
}

DYMOLA_STATIC double derivativeIni(double startTime, double u)
{
      int derID;
      int buffersize = 5;
      char mess[500];
	  struct DymosimSimulator*dymosimData;
	  dymosimData= dymosimGetThreadData();

      if (dymosimData->lastDerID >= MAX_DERIVATIVE-1) {
         sprintf(mess,"The maximum number of derivatives (= %d) is reached.\n"
                "No more delay memory is available\n", (int) MAX_DERIVATIVE);
         DymosimError(mess);
      }
      ++ dymosimData->lastDerID;
      derID = dymosimData->lastDerID;
   
      dymosimData->deri[derID].nx = buffersize;
      dymosimData->deri[derID].timedelay = 0.0;
      dymosimData->deri[derID].x  = (double *) malloc( sizeof (double) * buffersize * 2);
	   if (!dymosimData->deri[derID].x) {
		  sprintf(mess,"Failed to allocate memory for delay.\n You might decrease the number of delays\n "
			  " or the 'double Buffersize=%d;' in dymola/source/dsblock5.c\n",buffersize);
		  DymosimError(mess);
	  }
      dymosimData->deri[derID].y  = dymosimData->deri[derID].x + buffersize;
   
      dymosimData->deri[derID].x[0] = startTime - 1.0e6;
                                          /* To make sure that x[0] is smaller than x[1]
                                            a constant value of 1.0 is substracted from x[0]. */
      dymosimData->deri[derID].x[1] = startTime;      
   
      dymosimData->deri[derID].y[0] = u;               /* <u>,here the inital u  */
      dymosimData->deri[derID].y[1] = u;               /* Extrapolation backwards will give constant u. */
      dymosimData->deri[derID].first = 0;             
      dymosimData->deri[derID].add = 1;                /* at this position the last element
                                             was placed */
      dymosimData->deri[derID].old = 1;                /* set initial interpolation position;
                                             at this value <delayget> will start
                                             finding the upper and lower bounds  */
   
      return derID;
}

DYMOLA_STATIC void delayDerivativeClose()
{
      int delayID = 0;                      
      int derID = 0;
	  struct DymosimSimulator*dymosimData;
	  dymosimData= dymosimGetThreadData();
   
      while(delayID <= dymosimData->lastDelayID){      /* free storage for all delays */    
         free(dymosimData->del[delayID].x);
         ++delayID;
      }
   
      while(derID <= dymosimData->lastDerID){          /* free storage for all derivatives */      
         free(dymosimData->deri[derID].x);
         ++derID;
      }
   
      dymosimData->lastDelayID = -1;                   /* reset counter for delays */                  
      dymosimData->lastDerID = -1;                     /* reset counter for derivatives */ 

/*    DymosimMessage("delay + derivative storage freed"); */
}

DYMOLA_STATIC double delayFunction(double idd, double delaytime, double maxDelayTime, double t, double u, const char*exprStr)
{      
      double dummy, y;
	  if (delaytime>maxDelayTime*1.00001) {
		  char str[1000];
		  sprintf(str,"Delay time %g exceeded maximum delay time %g in \"%.400s\"\n",delaytime,maxDelayTime,exprStr?exprStr:"");
		  DymosimError(str);
	  }
      dummy = delayWrite(&idd,&t,&u);     /* call delayWrite before ...           */
      y = delayRead(&idd,&delaytime,&t);  /*                    ... delayRead      */
      return (y);
}
static void delayDWrite(int id,double expr,double Time) {
	struct DymosimSimulator*dymosimData;
	dymosimData= dymosimGetThreadData();
	while (Time <= dymosimData->del[id].x[dymosimData->del[id].add]) {  
		dymosimData->del[id].add = dymosimData->del[id].add - 1;
		if (dymosimData->del[id].add < 0)
			dymosimData->del[id].add = dymosimData->del[id].nx - 1;
    }
	if (dymosimData->del[id].y[dymosimData->del[id].add]==expr) 
		return;

	dymosimData->del[id].add++;
    if (dymosimData->del[id].add > dymosimData->del[id].nx-1)
        dymosimData->del[id].add = 0;
   
   /* Update first position if we are removing the oldest value. */
   if (dymosimData->del[id].add == dymosimData->del[id].first) {
	   dymosimData->del[id].first++;
	   if (dymosimData->del[id].first>dymosimData->del[id].nx-1)
		   dymosimData->del[id].first=0;
   }
   dymosimData->del[id].x[dymosimData->del[id].add]=Time;
   dymosimData->del[id].y[dymosimData->del[id].add]=expr;
}
static int delayDnext(int id,double x,double*timeNext) {
	struct DymosimSimulator*dymosimData;
	dymosimData= dymosimGetThreadData();
	if (x >= dymosimData->del[id].x[dymosimData->del[id].add]) {
      /* Extrapolation to future. */
          /* sprintf(mess,"Delay No. %d: "
                    "Extrapolation to future occured at time %g \n", id, *t);
             DymosimMessage(mess); */
       /* Set second point for interpolation to the last point in buffer. */
         dymosimData->del[id].old = dymosimData->del[id].add;
		 return 0;
      } 
      else if (x < dymosimData->del[id].x[dymosimData->del[id].first]) {
      /* Extrapolation to past. */
		    char mess[500];
            double buffersize = dymosimData->del[id].nx;
            sprintf(mess,"Extrapolation to past occured in Delay-Block No. %d: \n"
                   "Buffersize(=%g) too small or too many changes for discrete variable\n"
		   "for chosen simulation settings\n"
		   "You might increase the double Buffersize=... in dymola/source/dsblock5.c", id, buffersize);
          /*  DymosimMessage(mess); */
            DymosimError(mess); 
	}
	if(x >= dymosimData->del[id].x[dymosimData->del[id].old]) {
      /* Search forward from previous time. */
		for(;;) {
			int newOld=dymosimData->del[id].old+1;
			if (newOld>dymosimData->del[id].nx-1) newOld=0;
			*timeNext=dymosimData->del[id].x[newOld];
			if (x<*timeNext) {
				return 1;
			}
			dymosimData->del[id].old=newOld;
		}
      } 
      else {
      /* Search backward from previous time. */
		  for(;;) {
			  volatile double d;
			  int newOld=dymosimData->del[id].old-1;
			  if (newOld<0) newOld=dymosimData->del[id].nx-1;
			  d=dymosimData->del[id].x[newOld];
			  dymosimData->del[id].old=newOld;
			  if (x>=d) {
				  *timeNext=dymosimData->del[id].x[dymosimData->del[id].old];
				  return 1;
			  }
		  }
	  }
}

DYMOLA_STATIC void registerTimeEvent(const double atTime);
DYMOLA_STATIC double delayDDFunction(double expr,double dt,double*idd,
							  int BufferSize,double Time,int Event,int*timed) {
	  struct DymosimSimulator*dymosimData;
	  double timeNext;
	  int delayId;
	  dymosimData= dymosimGetThreadData();

	  if (*idd==0) {
		  *idd=1+delayIni(dt,BufferSize,Time,expr);
		  delayId=(int)(*idd+0.1)-1;
		  dymosimData->del[delayId].add=dymosimData->del[delayId].old=0;
	  } else 
		  delayId=(int)(*idd+0.1)-1;
	  if (Event) delayDWrite(delayId,expr,Time);
	  if (Event && delayDnext(delayId,Time-dt,&timeNext)) {
		  if (Time<timeNext-4e-14*(fabs(Time)+dymosimData->modelData.basicD->mOrigTimeError)) {
			  registerTimeEvent(timeNext);
			  *timed=0;
		  } else {
			  *timed=1;
		  }
	  } else {
		  *timed=0;
	  }
	  return dymosimData->del[delayId].y[dymosimData->del[delayId].old];
}
DYMOLA_STATIC double delayDCFunction(double expr,double dt,double*idd,int BufferSize,double Time,int Event, 
							  double*rel,double*qp,double*qn,int*qen,double*qz2,int*AnyEvent) {
	  double timeNext;
	  int delayId;
	  struct DymosimSimulator*dymosimData;
	  dymosimData= dymosimGetThreadData();
	  if (*idd==0) {
		  *idd=1+delayIni(dt,BufferSize,Time,expr);
		  delayId=(int)(*idd+0.1)-1;
		  dymosimData->del[delayId].add=dymosimData->del[delayId].old=0;
	  } else 
		  delayId=(int)(*idd+0.1)-1;
	  if (Event) delayDWrite(delayId,expr,Time);
	  if (Event) {
		  int oldD=dymosimData->del[delayId].old;
		  delayDnext(delayId,Time-dt,&timeNext);
		  if (oldD!=dymosimData->del[delayId].old)
			  *AnyEvent=1;
	  }
	  *rel=Time-dt-dymosimData->del[delayId].x[dymosimData->del[delayId].old];
	  qz2[0] = -*rel;
	  if (dymosimData->del[delayId].old==dymosimData->del[delayId].add) {
		 qz2[1]=1;
	  } else {
		int oldNext=dymosimData->del[delayId].old+1;
		if (oldNext>dymosimData->del[delayId].nx-1) oldNext=0;
		qz2[1]=-(Time-dt-dymosimData->del[delayId].x[oldNext])+1e-16;
	  }
	  return dymosimData->del[delayId].y[dymosimData->del[delayId].old];
}


DYMOLA_STATIC double delayWrite(double *idd, double *t, double *u)
{
      int id = (int) (*idd + 0.1);
   	  struct DymosimSimulator*dymosimData;
	  dymosimData= dymosimGetThreadData();
   /* Remove "future" values if any. */
      while (*t <= dymosimData->del[id].x[dymosimData->del[id].add]) {  
         dymosimData->del[id].add = dymosimData->del[id].add - 1;
         if (dymosimData->del[id].add < 0)
            dymosimData->del[id].add = dymosimData->del[id].nx - 1;
      }
   
   /* Update last position. */
      dymosimData->del[id].add++;
      if (dymosimData->del[id].add > dymosimData->del[id].nx-1)
         dymosimData->del[id].add = 0;
   
   /* Update first position if we are removing the oldest value. */
      if (dymosimData->del[id].add == dymosimData->del[id].first) {
#if 1
		  /* Throw away 1-keepnom/keepdenom of first 0.7 of values */
		  /* Better than simply stopping */
		  int id2=(dymosimData->del[id].first+(int)(dymosimData->del[id].nx*0.7)) % dymosimData->del[id].nx;
		  int iold=id2,inew=id2;
		  const int keepnom=3,keepdenom=4;
		  int keepcounter=0;
		  for(;;) {
			  dymosimData->del[id].x[inew]=dymosimData->del[id].x[iold];
			  dymosimData->del[id].y[inew]=dymosimData->del[id].y[iold];
			  if (iold==dymosimData->del[id].first) break;
			  iold--;
			  if (iold<0) iold=dymosimData->del[id].nx-1;
			  keepcounter++;
			  if (keepcounter>=keepdenom) keepcounter=0;
			  if (keepcounter<keepnom) {
				  inew--;
				  if (inew<0) inew=dymosimData->del[id].nx-1;
			  }
		  }
		  dymosimData->del[id].first=inew;
#else
         dymosimData->del[id].first++;
         if (dymosimData->del[id].first > dymosimData->del[id].nx-1)
            dymosimData->del[id].first = 0;
#endif
      }
   
   /* Store values. */
      dymosimData->del[id].x[dymosimData->del[id].add] = *t;        /* store new t */
      dymosimData->del[id].y[dymosimData->del[id].add] = *u;        /* store new u */
   
      return (*u);   
}

DYMOLA_STATIC double delayRead(double *idd, double *delaytime, double *t)
{
      int id = (int) (*idd + 0.1);        /* convert id to integer. */
      double x, xup, xlow;
      double y, yup, ylow;
      int oldold;
      char mess[500];
      double buffersize;
	  struct DymosimSimulator*dymosimData;
	  dymosimData= dymosimGetThreadData();

      oldold = dymosimData->del[id].old;
      dymosimData->del[id].timedelay = *delaytime;
      x = *t - *delaytime;                /* calculate interpolation x */
   
      if (x > dymosimData->del[id].x[dymosimData->del[id].add]) {
      /* Extrapolation to future. */
          /* sprintf(mess,"Delay No. %d: "
                    "Extrapolation to future occured at time %g \n", id, *t);
             DymosimMessage(mess); */
       /* Set second point for interpolation to the last point in buffer. */
         dymosimData->del[id].old = dymosimData->del[id].add;
      } 
      else if (x < dymosimData->del[id].x[dymosimData->del[id].first]) {
      /* Extrapolation to past. */
            buffersize = dymosimData->del[id].nx;
            sprintf(mess,"Extrapolation to past occured in Delay-Block No. %d: \n"
                   "Buffersize(=%g) too small or DelayTime(=%g sec) too big\n"
		   "for chosen simulation settings\n"
		   "You might increase the double Buffersize=... in dymola/source/dsblock5.c", id, buffersize, *delaytime);
          /*  DymosimMessage(mess); */
            DymosimError(mess); 
       /* Set second point for interpolation to the first+1 point in buffer. */
         dymosimData->del[id].old = dymosimData->del[id].first + 1;
         if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
            dymosimData->del[id].old = 0;
      } 
      else if (x > dymosimData->del[id].x[dymosimData->del[id].old]) {
      /* Search forward from previous time. */
         while (x > dymosimData->del[id].x[dymosimData->del[id].old]) {
            dymosimData->del[id].old++;
            if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
               dymosimData->del[id].old = 0;
         }
      } 
      else {
      /* Search backward from previous time. */
         while (x <= dymosimData->del[id].x[dymosimData->del[id].old] && dymosimData->del[id].old!=dymosimData->del[id].first) {
            dymosimData->del[id].old--;
            if (dymosimData->del[id].old < 0)
               dymosimData->del[id].old = dymosimData->del[id].nx-1;
         }
      
      /* old should be second point for interpolation. */
         dymosimData->del[id].old++;
         if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
            dymosimData->del[id].old = 0;
      }
   
      xup = dymosimData->del[id].x[dymosimData->del[id].old];       /* calculate upper bound for interpolation */
      if (dymosimData->del[id].old > 0)                /* calculate xlow               */
         xlow = dymosimData->del[id].x[dymosimData->del[id].old-1];
      else
         xlow = dymosimData->del[id].x[dymosimData->del[id].nx-1];
   
      yup = dymosimData->del[id].y[dymosimData->del[id].old];       /* calculate final yup */
      if (dymosimData->del[id].old > 0)                /* calculate final ylow */
         ylow = dymosimData->del[id].y[dymosimData->del[id].old-1];
      else
         ylow = dymosimData->del[id].y[dymosimData->del[id].nx-1];
   
   /* The interpolation/extrapolation formula is given by: */
      y = ylow + (x - xlow) * (yup - ylow)/(xup - xlow);
   
      return (y);
}


DYMOLA_STATIC double derivativeFunction(double idd, double t, double u)
{      
      double dummy, y;
      dummy = derivWrite(&idd,&t,&u);     /* call derivWrite before ...            */
      y = derivRead(&idd,&t);             /*                    ... derivRead      */
      return (y);
}

DYMOLA_STATIC double derivWrite(double *idd, double *t, double *u)
{
   double epsilon = 1.E-11;
   int id = (int) (*idd + 0.2) ;
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();
   if (*t > dymosimData->deri[id].x[dymosimData->deri[id].add]+epsilon){  /* new time > old time */
       ++dymosimData->deri[id].add;
       if (dymosimData->deri[id].add > dymosimData->deri[id].nx-1) {
           dymosimData->deri[id].add = 0;
       }
       dymosimData->deri[id].x[dymosimData->deri[id].add] = *t;     /* write new t */
       dymosimData->deri[id].y[dymosimData->deri[id].add] = *u;     /* write new u */
   }
   else if (*t < dymosimData->deri[id].x[dymosimData->deri[id].add]-epsilon){        /* new time < old time */
       while (*t <= dymosimData->deri[id].x[dymosimData->deri[id].add]-epsilon){     /* find new position   */
          if (dymosimData->deri[id].add >= 1)
             dymosimData->deri[id].add = dymosimData->deri[id].add - 1;
          else
             dymosimData->deri[id].add = dymosimData->deri[id].nx-1;
       }
       if (dymosimData->deri[id].add >= dymosimData->deri[id].nx-1)
          dymosimData->deri[id].add = 0;
       else
          ++dymosimData->deri[id].add;
       dymosimData->deri[id].x[dymosimData->deri[id].add] = *t;     /* write new t */
       dymosimData->deri[id].y[dymosimData->deri[id].add] = *u;     /* write new u */
   }
   else                                   /* new time = old time  */
       ;                                  /* don't write anything */
   return (*u);   
}

DYMOLA_STATIC double derivRead(double *idd, double *t)
{
   int id = (int) (*idd + 0.2);
   double x, xup, xlow;
   double y, yup, ylow;
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();
   x = *t;                                 /* calculate interpolation x     */

   xup = dymosimData->deri[id].x[dymosimData->deri[id].old];         /* calculate old upper bound as
                                              first guess for interpolation */
   while (x > xup){                        /* iterate, until x is bigger then xup  */
        xlow = xup;
        ++dymosimData->deri[id].old;                    /* increase xup */
        if (dymosimData->deri[id].old > dymosimData->deri[id].nx-1) dymosimData->deri[id].old = 0;
        xup  = dymosimData->deri[id].x[dymosimData->deri[id].old];
        if (xlow > xup){                   /* extrapolation into future */
           dymosimData->deri[id].old = dymosimData->deri[id].old - 1;/* decrease xup */
           if (dymosimData->deri[id].old < 0) dymosimData->deri[id].old = dymosimData->deri[id].nx-1 ;
           xup = x;                        /* terminate loop  */
        }
   }
   if (dymosimData->deri[id].old >= 1)                  /* calculate xlow               */
      xlow = dymosimData->deri[id].x[dymosimData->deri[id].old-1];
   else
      xlow = dymosimData->deri[id].x[dymosimData->deri[id].nx-1];

   yup = dymosimData->deri[id].y[dymosimData->deri[id].old];         /* calculate final yup */
   if (dymosimData->deri[id].old >= 1)                  /* calculate final ylow */
      ylow = dymosimData->deri[id].y[dymosimData->deri[id].old-1];
   else
      ylow = dymosimData->deri[id].y[dymosimData->deri[id].nx-1];
                                           /* calculate derivative */
   y = (yup - ylow)/(xup - xlow);

   return (y);
}

/****************************************************************************************
 the following functions are required for the Block library of
 Dymola version 3.0 or older, but not for version 3.1
 ****************************************************************************************/

DYMOLA_STATIC double delayinit(double delaytime, double buffer, double u)
{
   static const double maxfuture = -100.0; /* negative delay means:
                                        "extrapolation into future".
                                        The negative delay is limited to
                                        100 sconds. This means that at 
                                        current time t the value of t+100
                                        would be extrapolated */
   int buffersize = (int) (buffer + 0.1); 
                                     /* buffersize for storage allocation */
   int id;
                                     /* this part is called only once during
                                        the initialisation  (init = 1)    */
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();

   if (dymosimData->delayinit > 0){
      id = dymosimData->oldid;
      if (delaytime < maxfuture){
        DymosimMessage("Extrapolation limit into future exeeded; DelayTime < -100s");
	  /* *QiErr_ = 1; */
      delaytime = maxfuture; /* just to fix the problem here      */
      }
      ++ dymosimData->oldid;
      ++ dymosimData->delays;
      if (dymosimData->oldid >= maxid){
        DymosimMessage("Maximum number of delays (maxid) exeeded");
	  /* *QiErr_ = 1;   */
         dymosimData->oldid = 0;                  /* just to fix the problem here       */
      }
      dymosimData->del[id].nx = buffersize;
      dymosimData->del[id].timedelay = delaytime;
      dymosimData->del[id].x  = (double *) malloc( sizeof (double) * buffersize * 2);
      dymosimData->del[id].y  = dymosimData->del[id].x + buffersize;
                                     /* the first time value of the buffer is
                                        the negative value of the delaytime.
                                        The (negative) <maxfuture> is added in
                                        order to cope with negative delays as
                                        well (extrapolation into future)    */
	  
      dymosimData->del[id].x[0] = -1;
      dymosimData->del[id].x[1] = 0; /* Assuming StartTime=0 */

      dymosimData->del[id].y[0] = u;              /* <u>,here the inital u               */
      dymosimData->del[id].y[1] = u;              /* Extrapolation backwards will give constant u. */
      dymosimData->del[id].first = 0;             
      dymosimData->del[id].add = 1;               /* at this position the last element
                                        was placed */
      dymosimData->del[id].old = 1;               /* set initial interpolation position;
                                        at this value <delayget> will start
                                        finding the upper and lower bounds  */
   } 
   else {
      id = dymosimData->oldid;
      dymosimData->del[id].timedelay = delaytime;
      dymosimData->oldid++;
      if (dymosimData->oldid >= dymosimData->delays) 
		  dymosimData->oldid = 0;
   }
   return ( (double) id);
}

DYMOLA_STATIC void delayiniclos()
{
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();
   dymosimData->delayinit  = 0;                        /* after initialisation                 */
   dymosimData->oldid = 0;
}

DYMOLA_STATIC void delayclose()
{
   int id = 0;                       /* free storage for all delays          */
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();

   while(id < dymosimData->delays){               
      free(dymosimData->del[id].x);
      ++id;
  }
                                     /* set initial conditions for a
                                        new simulation                       */
   dymosimData->oldid  = 0;                       
   dymosimData->delays = 0;
   dymosimData->delayinit   = 1;
}

DYMOLA_STATIC double delayfunc(double delaytime, double t, double u, double buffersize)
{      
   double idd;
   double dummy, y;
   idd = delayinit(delaytime,buffersize,u);
   dummy = delayput(&idd,&t,&u);     /* call delayput before ...             */
   y = delayget(&idd,&t);            /*                    ... delayget      */
   return (y);
}

DYMOLA_STATIC double delayput(double *idd, double *t, double *u)
{
   int id = (int) (*idd + 0.1);
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();

   /* Remove "future" values if any. */
   while (*t <= dymosimData->del[id].x[dymosimData->del[id].add]) {  
/*
	   if (*t < dymosimData->del[id].x[dymosimData->del[id].add])
		   printf("Removing: new time < old time %g < %g \n", *t, dymosimData->del[id].x[dymosimData->del[id].add]);
*/
       dymosimData->del[id].add = dymosimData->del[id].add - 1;
	   if (dymosimData->del[id].add < 0)
           dymosimData->del[id].add = dymosimData->del[id].nx - 1;
       }

   /* Update last position. */
   dymosimData->del[id].add++;
   if (dymosimData->del[id].add > dymosimData->del[id].nx-1)
       dymosimData->del[id].add = 0;
   
   /* Update first position if we are removing the oldest value. */
   if (dymosimData->del[id].add == dymosimData->del[id].first) {
       dymosimData->del[id].first++;
       if (dymosimData->del[id].first > dymosimData->del[id].nx-1)
           dymosimData->del[id].first = 0;
   }

   /* Store values. */
   dymosimData->del[id].x[dymosimData->del[id].add] = *t;                 /* store new t */
   dymosimData->del[id].y[dymosimData->del[id].add] = *u;                 /* store new u */
   
   return (*u);   
}

DYMOLA_STATIC double delayget(double *idd, double *t)
{
   int id = (int) (*idd + 0.1);     /* convert id to integer. */
   double x, xup, xlow;
   double y, yup, ylow;
   int oldold;
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();

   oldold = dymosimData->del[id].old;
   x = *t - dymosimData->del[id].timedelay;      /* calculate interpolation x */

   if (x > dymosimData->del[id].x[dymosimData->del[id].add]) {
	   /* Extrapolation to future. */
	   printf("Warning: Extrapolation to future %g at time %g \n", x, *t);

       /* Set second point for interpolation to the last point in buffer. */
       dymosimData->del[id].old = dymosimData->del[id].add;
   } else if (x < dymosimData->del[id].x[dymosimData->del[id].first]) {
	   /* Extrapolation to past. */
	   if (x > 0)
		   printf("Warning: Extrapolation to past %g at %g \n", x, *t);

       /* Set second point for interpolation to the first+1 point in buffer. */
       dymosimData->del[id].old = dymosimData->del[id].first + 1;
	   if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
           dymosimData->del[id].old = 0;
   } else if (x > dymosimData->del[id].x[dymosimData->del[id].old]) {
	   /* Search forward from previous time. */
	   while (x > dymosimData->del[id].x[dymosimData->del[id].old]) {
           dymosimData->del[id].old++;
           if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
               dymosimData->del[id].old = 0;
	   }
   } else {
	   /* Search backward from previous time. */
	   while (x <= dymosimData->del[id].x[dymosimData->del[id].old]) {
           dymosimData->del[id].old--;
           if (dymosimData->del[id].old < 0)
               dymosimData->del[id].old = dymosimData->del[id].nx-1;
	   }

	   /* old should be second point for interpolation. */
	   dymosimData->del[id].old++;
       if (dymosimData->del[id].old > dymosimData->del[id].nx-1)
           dymosimData->del[id].old = 0;
   }
/*
   if (fabs(dymosimData->del[id].old - oldold) > 10)
       printf("Much searching %d %d \n", dymosimData->del[id].old, oldold);
*/
   xup = dymosimData->del[id].x[dymosimData->del[id].old];       /* calculate upper bound for interpolation */
   if (dymosimData->del[id].old > 0)                /* calculate xlow               */
      xlow = dymosimData->del[id].x[dymosimData->del[id].old-1];
   else
      xlow = dymosimData->del[id].x[dymosimData->del[id].nx-1];

   yup = dymosimData->del[id].y[dymosimData->del[id].old];             /* calculate final yup */
   if (dymosimData->del[id].old > 0)                     /* calculate final ylow */
      ylow = dymosimData->del[id].y[dymosimData->del[id].old-1];
   else
      ylow = dymosimData->del[id].y[dymosimData->del[id].nx-1];

   /* The interpolation/extrapolation formula is given by: */

   y = ylow + (x - xlow) * (yup - ylow)/(xup - xlow);
/*
   if (id == 5 && (dymosimData->del[id].old != 1 || x > 0) )
	   printf("Delay time %g at time %g index %d value %g\n", x, *t, dymosimData->del[id].old, y);
*/   
   if (yup > ylow) {
	   if (y > yup )
	       y = yup;
       else if (y < ylow)
	       y = ylow;
   } else {
	   if (y < yup )
	       y = yup;
       else if (y > ylow)
	       y = ylow;
   }

   return (y);
}


DYMOLA_STATIC double derivfunc(double t, double u)
{      
   double dummy, y;
   double idd;
   idd = delayinit(0.0,5.0,u);
   dummy = derivput(&idd,&t,&u);     /* call derivput before ...             */
   y = derivget(&idd,&t);            /*                    ... derivget      */
   return (y);
}

DYMOLA_STATIC double derivput(double *idd, double *t, double *u)
{
   double epsilon = 1.E-11;
   int id = (int) (*idd + 0.2) ;
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();
   if (*t > dymosimData->del[id].x[dymosimData->del[id].add]+epsilon){             /* new time > old time */
       ++dymosimData->del[id].add;
       if (dymosimData->del[id].add > dymosimData->del[id].nx-1) {
           dymosimData->del[id].add = 0;
       }
       dymosimData->del[id].x[dymosimData->del[id].add] = *t;                 /* write new t */
       dymosimData->del[id].y[dymosimData->del[id].add] = *u;                 /* write new u */
   }
   else if (*t < dymosimData->del[id].x[dymosimData->del[id].add]-epsilon){        /* new time < old time */
       while (*t <= dymosimData->del[id].x[dymosimData->del[id].add]-epsilon){        /* find new position   */
          if (dymosimData->del[id].add >= 1)
             dymosimData->del[id].add = dymosimData->del[id].add - 1;
          else
             dymosimData->del[id].add = dymosimData->del[id].nx-1;
       }
       if (dymosimData->del[id].add >= dymosimData->del[id].nx-1)
          dymosimData->del[id].add = 0;
       else
          ++dymosimData->del[id].add;
       dymosimData->del[id].x[dymosimData->del[id].add] = *t;                 /* write new t */
       dymosimData->del[id].y[dymosimData->del[id].add] = *u;                 /* write new u */
   }
   else                                          /* new time = old time  */
       ;                                            /* don't write anything */
   return (*u);   
}

DYMOLA_STATIC double derivget(double *idd, double *t)
{
   int id = (int) (*idd + 0.2);
   double x, xup, xlow;
   double y, yup, ylow;
   struct DymosimSimulator*dymosimData;
   dymosimData= dymosimGetThreadData();
   x = *t;                                 /* calculate interpolation x     */

   xup = dymosimData->del[id].x[dymosimData->del[id].old];           /* calculate old upper bound as
                                              first guess for interpolation */
   while (x > xup){                 /* iterate, until x is bigger then xup  */
        xlow = xup;
        ++dymosimData->del[id].old;                     /* increase xup */
        if (dymosimData->del[id].old > dymosimData->del[id].nx-1) dymosimData->del[id].old = 0;
        xup  = dymosimData->del[id].x[dymosimData->del[id].old];
        if (xlow > xup){                   /* extrapolation into future */
           dymosimData->del[id].old = dymosimData->del[id].old - 1;  /* decrease xup */
           if (dymosimData->del[id].old < 0) dymosimData->del[id].old = dymosimData->del[id].nx-1 ;
           xup = x;                        /* terminate loop  */
        }
   }
   if (dymosimData->del[id].old >= 1)                    /* calculate xlow               */
      xlow = dymosimData->del[id].x[dymosimData->del[id].old-1];
   else
      xlow = dymosimData->del[id].x[dymosimData->del[id].nx-1];

   yup = dymosimData->del[id].y[dymosimData->del[id].old];             /* calculate final yup */
   if (dymosimData->del[id].old >= 1)                     /* calculate final ylow */
      ylow = dymosimData->del[id].y[dymosimData->del[id].old-1];
   else
      ylow = dymosimData->del[id].y[dymosimData->del[id].nx-1];
                                            /* calculate derivative */
   y = (yup - ylow)/(xup - xlow);

   return (y);
}

