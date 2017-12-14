/* dsutil.h */
/*
 * Copyright (C) 1995-2001 Dynasim AB.
 * All rights reserved.
 *
 */

/* Utility macros and functions for DSblock.

   Author: Hilding Elmqvist, Dynasim AB, 1995-02-21
   Version: 1.8, 1996-09-30
            1.9, 1996-10-19: Added support for non-root finder.
            1.10 1996-10-24: DymosimMessageDouble, etc.
            1.11 1997-02-13: Correction of prototypes
            1.12 1997-04-29: Introduced macro cross_
	    1.13 1997-05-29: Fixed bugs in function macros, made faster.
            1.14 1997-11-16: Added gearwheel to PackShape
            1.15 1997-11-23: - CombiTable support.
                             - Longjmp introduced to stop model
                               evaluation immediately after an error.
                             - Fixed (minor) bugs in sqr(), setBoolean2/3.
                             - matError (global variable) used in
                               matrix I/O routines.
                             - new switch DYMOSIM, for Dymosim related code.
            1.16 1998-01-20  - Changed TimeEventAccuracy for Sample to 1E-12.
                             - Added functions for Memory operator.
                             - Modified pow for Simulink
            1.17 1998-02-05: - solution of compatible singular systems added.
                             - new signal definition routines
                               blo3co_ (signal is constant) 
                               blo3sa_, blo3sb_, blo3ta_ 
                               (scalar/matrix signal is an alias).
                               blo3st_, blo3pt_ (data type of signal/parameter).
                             - signum-macro added
            1.18 1998-03-19: Introduced macro BreakDeclareFunction and
                             BreakEquationsFunction for handling of large 
                             dsblockb.
            1.19 1998-06-01: Introduced CheckForEvents
            1.20 1998-10-05: Modified for dSPACE realtime
            1.21 1999-01-20: Updated for DYMOLA_DSPACE, added new message routines
            1.22 1999-01-23: Introduced new handling of the Sample function
            1.23 1999-05-11: Removed calls of sprintf() for MATLAB/WATCOM 11.
*/

#ifndef DSUTIL_H
#define DSUTIL_H

#include <string.h>
#if defined(DYMOLA_DSPACE)
#include <dsdefs.h>
#else
#include <stdio.h>
#endif
#if defined(RTLAB)
#include <OpalPrint.h>
#endif
#if !defined(DYMOLA_STATIC)
#if defined(__cplusplus)
#define DYMOLA_STATIC extern
#elif defined(RT) && !defined(DYM2DS)
#define DYMOLA_STATIC static
#else
#define DYMOLA_STATIC
#endif
#endif
#if !defined(DSE_STRUCT)
 #if defined(DS_EMBEDDED)
  #define DSE_STRUCT sts->
 #else
  #define DSE_STRUCT
 #endif
#endif
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "delay.h"
#include "dymtable.h"
#include "matutil.h"
#include "dymutil.h"
#include "sprwat.h"

/* General handling */



#ifndef beginParallelSection
#define beginParallelSection(layer, section)
#endif
#if defined(LIBDS_DLL) && defined(DYN_MULTINSTANCE)
#define beginJmpParallelSections {struct MyJmpBuf saved_jmp_buf_env;int DYNLocalError=0;struct DymosimSimulator*saved_threadData;saved_jmp_buf_env=DYNGlobal_jmp_buf_env;saved_threadData=dymosimGetThreadData();
#define beginJmpParallelSection dymosimSetThreadData(saved_threadData);DYNPropagateDidToThread(did_);if (setjmp(DYNGlobal_jmp_buf_env.TheBuffer)==0) {
#define endJmpParallelSection } else DYNLocalError=1;
#define endJmpParallelSections DYNGlobal_jmp_buf_env=saved_jmp_buf_env;if (DYNLocalError) {GlobalError_=DYNLocalError;longjmp(DYNGlobal_jmp_buf_env.TheBuffer, 1);}}
#else
#define beginJmpParallelSections {struct MyJmpBuf saved_jmp_buf_env;int DYNLocalError=0;saved_jmp_buf_env=DYNGlobal_jmp_buf_env;
#define beginJmpParallelSection DYNPropagateDidToThread(did_);if (setjmp(DYNGlobal_jmp_buf_env.TheBuffer)==0) {
#define endJmpParallelSection } else DYNLocalError=1;
#define endJmpParallelSections DYNGlobal_jmp_buf_env=saved_jmp_buf_env;if (DYNLocalError) {GlobalError_=DYNLocalError;longjmp(DYNGlobal_jmp_buf_env.TheBuffer, 1);}}
#endif
#ifndef endParallelSection
#define endParallelSection(layer, section)
#endif

#include "ModelicaUtilities.h"
struct DYNInstanceData;
DYMOLA_STATIC void ModelicaVFormatError(const char *string, va_list ap) {
	char buf[4000];
#if defined(__WATCOMC__)  && defined(DynSimStruct) || defined(NO_FILE) || defined(DYMOLA_DSPACE)
	strcpy(buf,string);
#elif defined(_MSC_VER) && _MSC_VER>=1200
	_vsnprintf(buf,sizeof(buf)/sizeof(*buf),string,ap);
#else
	vsprintf(buf,string,ap);
#endif
	ModelicaFormatError("%s",buf);
}
DYMOLA_STATIC void ModelicaVFormatMessage(const char *string, va_list ap) {
	char buf[4000];
#if defined(__WATCOMC__)  && defined(DynSimStruct) || defined(NO_FILE) || defined(DYMOLA_DSPACE)
	strcpy(buf,string);
#elif defined(_MSC_VER) && _MSC_VER>=1200
	_vsnprintf(buf,sizeof(buf)/sizeof(*buf),string,ap);
#else
	vsprintf(buf,string,ap);
#endif
	ModelicaFormatMessage("%s",buf);
}
struct FunctionContext_ {
	char*text;
	struct FunctionContext_*next;
};
#include <setjmp.h>
struct MyJmpBuf {
	jmp_buf TheBuffer;
};
#if defined(DYN_MULTINSTANCE)
#ifndef DYN_MarkObject
#define DYN_MarkObject
typedef double Real;
#if defined(DYM2CCUR)
typedef int Integer;
#else
typedef int Integer;
#endif
typedef const char* String;
typedef Integer SizeType;

struct BufferObject {Real *Realbuffer;Integer *Integerbuffer;SizeType* Sizebuffer;String* Stringbuffer;};
struct MarkObject {struct BufferObject place,mark;};
#endif
struct DYN_ThreadData {
	struct FunctionContext_*m_global;
	int m_external;
	struct FunctionContext_ m_context;
	struct MarkObject m_start, m_current;
	String m_stringmark;
	String m_startstringmark;
	String m_endsimplestring;
	Real*m_endreal;
	Integer*m_endinteger;
	SizeType*m_endsize;
	String* m_endstring;
	struct MyJmpBuf m_jmp_buf_env;
	struct DYNInstanceData* did;
};
static struct DYN_ThreadData* DYN_GetThreadData();
DYMOLA_STATIC void DYNPropagateDidToThread(struct DYNInstanceData*did) {
	DYN_GetThreadData()->did=did;
}
#else
DYMOLA_STATIC void DYNPropagateDidToThread(struct DYNInstanceData*did) {;}
#endif
#if defined(DYN_MULTINSTANCE)
#define FunctionContextGlobal_ (DYN_GetThreadData()->m_global)
#define FunctionExternalContext_ (DYN_GetThreadData()->m_external)
#define DYNGlobal_jmp_buf_env (DYN_GetThreadData()->m_jmp_buf_env)
#else
DYMOLA_STATIC struct FunctionContext_* FunctionContextGlobal_=0;
DYMOLA_STATIC int FunctionExternalContext_=0;
static struct MyJmpBuf DYNGlobal_jmp_buf_env; 
#if (defined(_OPENMP) && !defined(DISABLE_DYMOLA_OPENMP))
#pragma omp threadprivate(FunctionContextGlobal_)
#pragma omp threadprivate(FunctionExternalContext_)
#pragma omp threadprivate(DYNGlobal_jmp_buf_env)
#endif
#endif
#if DymolaNoGuard_
#define PushContext(a) int oldFunctionExternal=FunctionExternalContext_;
#define PopContext() FunctionExternalContext_=oldFunctionExternal;
#define PushModelContext(b,a) (FunctionExternalContext_=0),
#define PopModelContext() (FunctionExternalContext_=0)
#else
#if defined(DYN_MULTINSTANCE)
#define modelContext_ (DYN_GetThreadData()->m_context)
#else
static struct FunctionContext_ modelContext_={0,0};
#if (defined(_OPENMP) && !defined(DISABLE_DYMOLA_OPENMP))
#pragma omp threadprivate(modelContext_)
#endif
#endif

#define PushContext(a) int oldFunctionExternal=FunctionExternalContext_;struct FunctionContext_ alpha_={a};alpha_.next=FunctionContextGlobal_;FunctionContextGlobal_=&alpha_;
#define PopContext() FunctionContextGlobal_=alpha_.next;FunctionExternalContext_=oldFunctionExternal;
#define PushModelContext(b,a) (modelContext_.text=a,FunctionContextGlobal_=&modelContext_,FunctionExternalContext_=0),
#define PopModelContext() (FunctionContextGlobal_=0,FunctionExternalContext_=0)
#endif

static int DYNIncrementFExternal();

#ifdef DYMOSIM 
#if defined(LIBDS_DLL) || defined(LIBDS_API)
LIBDS_API void DymosimMessageDymosim(const char* message);
LIBDS_API void DymosimMessageDymosimSev(int severity, const char* message);
#endif
#if !defined(LIBDS_DLL)
LIBDS_API void disstr_(const char* line, int len);
#endif
extern double increment(double incr);
#endif

#ifdef DYM2DS
void d2ds_print0(const char*f, const char* msg);
void d2ds_print1(const char*f, const char* msg, double d);
void d2ds_print8(const char*f, const char*xexpr, const char*op, const char*yexpr, double x, const char*op2, double y, const char*t2, double t);
#endif

#if defined(DYM2CCUR) && defined(OMP_DYMOLA)
extern void simwb_msg(const char*msg);
#endif

DYMOLA_STATIC void fmu_logger(const char* message, int newline, int severity);

DYMOLA_STATIC void DymosimMessage(const char* message) {
#ifdef DYMOSIM 
#ifdef LIBDS_DLL
  DymosimMessageDymosim(message);
#else
  int i = strlen(message);
  disstr_(message, i);
#endif
#elif defined(RTLAB)
  OpalPrint("%s\n", message); 
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s\n", message);
#elif defined(DYM2DS)
  d2ds_print0("%s\n", message);
#elif defined(DYM2CCUR) && defined(OMP_DYMOLA)
  simwb_msg(message);
#elif defined(BUILDFMU)
  fmu_logger(message, 1, 0);
#else
  printf("%s\n", message); 
#endif
}

#if !defined(DYMOSIM) && !defined(LIBDS_DLL) 
static void DymosimMessageDymosimSev(int severity, const char*message) {
#if defined(BUILDFMU)
    fmu_logger(message, 1, severity);
#else
	DymosimMessage(message);
#endif
}
#endif

DYMOLA_STATIC void DymosimMessageNoNL(const char*message) {
#ifdef DYMOSIM
	LIBDS_API void aprint(int type, const char *str);
	aprint(0,(char*)(message));
#elif defined(RTLAB)
  OpalPrint("%s", message); 
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s", message); 
#elif defined(DYM2DS)
  d2ds_print0("%s", message);
#elif defined(DYM2CCUR) && defined(OMP_DYMOLA)
  simwb_msg(message);
#elif defined(BUILDFMU)
  fmu_logger(message, 0, 0);
#else
  printf("%s", message); 
#endif
}

#define homotopy(a,b) DYNhomotopy(a,b,did_)
DYMOLA_STATIC double DYNhomotopy(double actual, double simple,struct DYNInstanceData*did_);
DYMOLA_STATIC double DymolaTimerCounterSince(double*d,int i);
DYMOLA_STATIC double MyCPUTime(void);
DYMOLA_STATIC double MyCPUTime(void) {
	static int i=0;
	static double d;
	double res=DymolaTimerCounterSince(&d,i);
	i=1;
	return res;
}
#if defined(DYMOLA_DSPACE)
#define CurrentClockTime CPUClk
#else
#define CurrentClockTime MyCPUTime()
#endif

DYMOLA_STATIC void DymosimMessageDoubleSev(int severity, const char* message, double d) {
#if !defined(DynSimStruct)
  char textline[200];
  sprintf(textline, "%.160s %.16G", message, d);
  DymosimMessageDymosimSev(severity, textline);
#elif defined(RTLAB)
  OpalPrint("%s %.16G\n", message, d); 
#elif defined(BUILDFMU)
  fmu_logger(message, 1, severity);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s %.16G\n", message, d); 
#elif defined(DYM2DS)
  d2ds_print1("%s %.16G\n", message, d);
#else
  printf("%s %.16G\n", message, d); 
  
#endif
}
DYMOLA_STATIC void DymosimMessageDouble(const char* message, double d) {
	DymosimMessageDoubleSev(0, message, d);
}

DYMOLA_STATIC void DymosimMessageDoubleVector(const char* matrixname, double * d, int n) {
#if !defined(DynSimStruct)
  char text[100];
  char textline[2000];
  int i;

  textline[0] = '\0';
  strcat(textline, matrixname);
  strcat(textline, " = {");
  for (i = 0; i < n; i++) {
    if (i > 0)
      strcat(textline, ", ");
    sprintf(text, "%G", d[i]);
    strcat(textline, text);
  }
  strcat(textline, "}");
  DymosimMessage(textline);
#elif defined(RTLAB)
  int i;
  OpalPrint("%s = {", matrixname);
  for (i = 0; i < n; i++) {
    if (i > 0)
      OpalPrint(", ");
    OpalPrint("%G", d[i]);
  }
  OpalPrint("}\n");
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  int i;
  ssPrintf("%s = {", matrixname);
  for (i = 0; i < n; i++) {
    if (i > 0)
      ssPrintf(", ");
    ssPrintf("%G", d[i]);
  }
  ssPrintf("}\n");
#elif defined(DYM2DS)
  int i;
  d2ds_print0("%s = {", matrixname);
  for (i = 0; i < n; i++) {
    if (i > 0)
      d2ds_print0("%s", ", ");
	d2ds_print1("%s%G", "", d[i]);
  }
  d2ds_print0("%s\n", "}");
#else
  int i;
  printf("%s = {", matrixname);
  for (i = 0; i < n; i++) {
    if (i > 0)
      printf(", ");
    printf("%G", d[i]);
  }
  printf("}\n");
#endif
}

#define SetElement(Mat, i, j, nRow, val) \
    Mat[(i)-1 + ((j)-1)*(nRow)] = val

#define GetElement(Mat, i, j, nRow) \
    Mat[(i)-1 + ((j)-1)*(nRow)]

DYMOLA_STATIC void DymosimMessageDoubleMatrix(const char* matrixname, double * d, int m, int n, int MaxRow) {
/* Writes matrix in Modelica format.

  name = {
    {1, 2, 3},
    {4, 5, 6} };
*/
#if !defined(DynSimStruct)
  char text[100];
  char textline[300];
  int i, j;

  textline[0] = '\0';
  strcat(textline, matrixname);
  strcat(textline, " = ");
  strcat(textline, "{");
  DymosimMessage(textline);
  textline[0] = '\0';

  DymosimMessage("");
  for (i = 1; i <= m; i++) {
    strcat(textline, "{");
    for (j = 1; j <= n; j++) {
      if (j > 1)
        strcat(textline, ", ");
	  if (strlen(textline)>sizeof(textline)-100) {
			DymosimMessage(textline);
			textline[0] = '\0';
		}
      sprintf(text, "%G", GetElement(d, i, j, MaxRow));
      strcat(textline, text);
    }
    strcat(textline, "}");
    if (i < m)
      strcat(textline, ", ");
    DymosimMessage(textline);
    textline[0] = '\0';
  }
  DymosimMessage("");
  DymosimMessage("};");
#elif defined(RTLAB)
  int i, j;

  OpalPrint("%s = {\n", matrixname);

  for (i = 1; i <= m; i++) {
    OpalPrint("{");
    for (j = 1; j <= n; j++) {
      if (j > 1)
        OpalPrint(", ");
      OpalPrint("%G", GetElement(d, i, j, MaxRow));
    }
    OpalPrint("}");
    if (i < m)
      OpalPrint(", ");
    OpalPrint("\n");
  }
  OpalPrint("};\n");
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  int i, j;

  ssPrintf("%s = {\n", matrixname);

  for (i = 1; i <= m; i++) {
    ssPrintf("{");
    for (j = 1; j <= n; j++) {
      if (j > 1)
        ssPrintf(", ");
      ssPrintf("%G", GetElement(d, i, j, MaxRow));
    }
    ssPrintf("}");
    if (i < m)
      ssPrintf(", ");
    ssPrintf("\n");
  }
  ssPrintf("};\n");
#else
  int i, j;

  printf("%s = {\n", matrixname);

  for (i = 1; i <= m; i++) {
    printf("{");
    for (j = 1; j <= n; j++) {
      if (j > 1)
        printf(", ");
      printf("%G", GetElement(d, i, j, MaxRow));
    }
    printf("}");
    if (i < m)
      printf(", ");
    printf("\n");
  }
  printf("};\n");
#endif
}

DYMOLA_STATIC void appendVector(double * mat, int MaxRow, int MaxCol, int *nRow, double * vec, int MaxVec) {
  int i;
  *nRow += 1;
  for (i = 1; i <= MaxCol; i++) {
    SetElement(mat, *nRow, i, MaxRow, i<=MaxVec ? GetElement(vec, i, 1, MaxVec) : 0);
  }
}


DYMOLA_STATIC void DymosimMessageInt(const char* message, int i) {
#if !defined(DynSimStruct)
  char textline[200];

  sprintf(textline, "%.160s %i", message, i);
  DymosimMessage(textline);
#elif defined(RTLAB)
  OpalPrint("%s, %li\n", message, i);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s, %li\n", message, i);
#elif defined(DYM2DS)
  d2ds_print1("%s \n", message, (double)i);
#else
  printf("%s, %li\n", message, i);
#endif
}

DYMOLA_STATIC void DymosimMessageMatrixElement(char* name, int i, int j, double d) {
#if !defined(DynSimStruct)
  char textline[200];

  sprintf(textline, "  %.160s[%i, %i] = %G", name, i, j, d);
  DymosimMessage(textline);
#elif defined(RTLAB)
  OpalPrint("%s[%li, %li] = %G\n", name, i, j, d);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s[%li, %li] = %G\n", name, i, j, d);
#else
  printf("%s[%li, %li] = %G\n", name, i, j, d);
#endif
}



static double DymosimGetTime2();
DYMOLA_STATIC int* GlobalErrorPointer(void);
DYMOLA_STATIC double DymosimErrorLev(const char* message, int lev) {
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
	DymosimMessageDoubleSev(lev,(lev==1)?"The following was detected at time:" :"The following error was detected at time:", DymosimGetTime2());
    DymosimMessageDymosimSev(lev, message);
	if (FunctionContextGlobal_) {
		DymosimMessageDymosimSev(lev, "The stack of functions is:");
		for(;FunctionContextGlobal_;FunctionContextGlobal_=FunctionContextGlobal_->next) {
			DymosimMessageDymosimSev(lev, FunctionContextGlobal_->text);
		}
	}
  }
  if (lev==1) return 0.0;
  *(GlobalErrorPointer()) = 1;
  longjmp(DYNGlobal_jmp_buf_env.TheBuffer, 1);
  return 0.0;
}
DYMOLA_STATIC double DymosimError(const char* message) {
	DymosimErrorLev(message, 2);
	return 0;
}
DYMOLA_STATIC void AssertModelicaF(int b,const char*bs,const char*x) {
	if (!b) {
		DymosimMessageDymosimSev(2, bs);
		DymosimError(x);  /* should not return. */

	}
}
DYMOLA_STATIC void AssertModelicaF4(int b,const char*bs,const char*x,int lev,int*hi) {
	if (!b) {
		if (lev==1) {
			if (hi) {
				if (*hi==1) return; /* Skipping */
				*hi=1;
			}
			DymosimMessageDymosimSev(1, bs);
			DymosimErrorLev(x, 1);
		} else {
			DymosimMessageDymosimSev(2, bs);
			DymosimError(x);  /* should not return. */
		}
	}
}

DYMOLA_STATIC int DymosimLog(char* message, double v) {
  DymosimMessageDouble(message, v);
  return 0;
}

static double LogRelation(char *op, char *xexpr, char *yexpr, double x, double y, 
                          Dymola_bool val, double t) {
/*  Example: LogRelation(">", #x, #y, x, y, (x) > (y), Time) */
#if !defined(DynSimStruct)
  char buf[1000]; 
  char *boolval;
  boolval = "false";
  if (val) 
    boolval = "true";

  sprintf(buf, "  Relation %.400s %s %.400s (%g %s %g) became %s at time = %g", 
               xexpr, op, yexpr, x, op, y, boolval, t);
  DymosimMessage(buf);
#elif defined(RTLAB)
  OpalPrint("  Relation %s %s %s (%g %s %g) became %s at time = %g\n", 
               xexpr, op, yexpr, x, op, y, (val ? "true" : "false"), t);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("  Relation %s %s %s (%g %s %g) became %s at time = %g\n", 
               xexpr, op, yexpr, x, op, y, (val ? "true" : "false"), t);
#elif defined(DYM2DS)
  d2ds_print8("  Relation %s %s %s (%g %s %g) became %s at time = %g\n", 
               xexpr, op, yexpr, x, op, y, (val ? "true" : "false"), t);
#else
  printf("  Relation %s %s %s (%g %s %g) became %s at time = %g\n", 
               xexpr, op, yexpr, x, op, y, (val ? "true" : "false"), t);
#endif
  return 1.0;
}

static double VariableChanged(char *var, double val, double t) {
#if !defined(DynSimStruct)
  char buf[1000]; 
  sprintf(buf, "  Variable %.400s = %g at time %g", var, val, t);
  DymosimMessage(buf);
#elif defined(RTLAB)
  OpalPrint("  Variable %s = %g at time %g\n", var, val, t);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("  Variable %s = %g at time %g\n", var, val, t);
#else
  printf("  Variable %s = %g at time %g\n", var, val, t);
#endif
  return 1.0;
}

static double diverr(const char *xexpr, double x, const char *yexpr, double y) {
#if !defined(DynSimStruct)
  char buf[1000];
  sprintf(buf, "\nModel error - division by zero: (%.400s) / (%.400s) = (%g) / (%g)\n", xexpr, yexpr, x, y);
  DymosimError(buf);
#elif defined(RTLAB)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    OpalPrint("\nModel error - division by zero: (%s) / (%s) = (%g) / (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - division by zero");
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
	  ssPrintf("\nModel error - division by zero: (%s) / (%s) = (%g) / (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - division by zero");
#else
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    printf("\nModel error - division by zero: (%s) / (%s) = (%g) / (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - division by zero");
#endif
  return 1.0;
}


static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double divmacro(double x,const char*sx,double y,const char*sy) {
	return (y!=0.0) ? ( (double) (x) / (double) (y) ) :  diverr(sx,(x),sy,(y));
}

#if DymolaNoGuard_
#define divmacro(x,sx,y,sy) (((double)(x))/(y))
#endif


#if DymolaNoGuard_
static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
void GuardedError(const char*xexpr, double x,const char*op) {
	return;
}
#else
static void GuardedError(const char*xexpr, double x,const char*op) {
#if !defined(DynSimStruct)
  char buf[1000];
  sprintf(buf, "\nModel error - %s (%.400s) = %s (%g)\n", op,xexpr,op,x);
  DymosimError(buf);
#elif defined(RTLAB)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
	  OpalPrint("\nModel error - %s (%.400s) = %s (%g)\n", op,xexpr,op,x);
  }
  DymosimError("Model error - illegal value");
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    ssPrintf("\nModel error - %s (%.400s) = %s (%g)\n", op,xexpr,op,x);
  }
  DymosimError("Model error - illegal value");
#else
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    printf("\nModel error - %s (%.400s) = %s (%g)\n", op,xexpr,op,x);
  }
  DymosimError("Model error - illegal value");
#endif
}
#endif

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double logGuarded(double x,const char*sx) {
	if (x<=0) GuardedError(sx, x,"Modelica.Math.log");
	return log(x);
}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double log10Guarded(double x,const char*sx) {
	if (x<=0) GuardedError(sx, x,"Modelica.Math.log10");
	return log10(x);
}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double asinGuarded(double x,const char*sx) {
	if (x<-1 || x>1) GuardedError(sx, x,"Modelica.Math.asin");
	return asin(x);
}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double acosGuarded(double x,const char*sx) {
	if (x<-1 || x>1) GuardedError(sx, x,"Modelica.Math.acos");
	return acos(x);
}


/* For old models: */
#define div(x,y) \
  ( (y) != 0.0 ? ( (double) (x) / (double) (y) ) :  diverr(#x, (x), #y, (y)) )

/* div in Modelica spec */
static double divideDymola(double x,double y) {double quot=x/y;return (quot>=0)?floor(quot):ceil(quot);}
/* rem in Modelica spec */
static double remainderDymola(double x,double y) {return x-divideDymola(x,y)*y;}
static double modulusDymola(double x,double y) {return x-floor(x/y)*y;}

static double powerr(const char *xexpr, double x, const char *yexpr, double y) {
#if !defined(DynSimStruct)
  char buf[1000];
  sprintf(buf, "\nModel error - power: (%.400s) ^ (%.400s) = (%g) ^ (%g)\n", xexpr, yexpr, x, y);
  DymosimError(buf);
#elif defined(RTLAB)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
	  OpalPrint("\nModel error - power: (%s) ^ (%s) = (%g) ^ (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - power");
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    ssPrintf("\nModel error - power: (%s) ^ (%s) = (%g) ^ (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - power");
#else
  if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
    printf("\nModel error - power: (%s) ^ (%s) = (%g) ^ (%g)\n", xexpr, yexpr, x, y);
  }
  DymosimError("Model error - power");
#endif
  return 1.0;
}

static double powmacro(double x, const char* sx, double y, const char* sy)
{
  return (x == 0.0 && y <= 0.0) || (x < 0.0 && floor(y) != y) ?
    powerr(sx, x, sy, y) : pow(x, y);
}
static double powmacro2(double x, const char* sx, int y, const char* sy)
{
  return (x == 0.0 && y < 0) ?
    powerr(sx, x, sy, y) : pow(x, y);
}

#define pow(x,y) powmacro((x), #x, (y), #y)

#undef Dymola_abs
#define Dymola_abs(x) \
  fabs(x)

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double sqr(double x) {
	return x*x;
}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double sqrtGuarded(double x,const char*sx) {
	if (x>=0) return (sqrt)(x);
	else {
		GuardedError(sx, x, "sqrt");
		return 0;
	}
}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double sqrt__(double x) {
	static const double lim=0;
	if (x>lim) return (sqrt)(x);
	else if (x>0) return x*(sqrt)(lim)/lim;
	else return 0;
}
static double sqrtder(double x) {
	static const double lim=0;
	if (x>lim) return 0.5/(sqrt)(x);
	else if (x>0) return (sqrt)(lim)/lim;
	else return 0;
}
#define sqrt(x) sqrt__(x)

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double Dymola_exp(double x) {
	static const double lim=690.8;
	if (x<lim) return (exp)(x);
	return (exp)(lim);
}
#define exp(x) Dymola_exp(x)
/*
  (x < log(DBL_MAX/10) ? exp(x) :  DBL_MAX/10)
*/
static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double Dymola_ln(double x) {
	static const double lim=1e-100;
	if (x>lim) return (log)(x);
	return (log)(1e-00);
}
#define ln(x) Dymola_ln(x)

#undef Dymola_min
#define Dymola_min(x,y) ((x) < (y) ? (x) : (y) )

#undef Dymola_max
#define Dymola_max(x,y) ((x) > (y) ? (x) : (y) )

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double RealBmin(double x,double y) {return ((x) < (y) ? (x) : (y) );}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double RealBmax(double x,double y) {return ((x) > (y) ? (x) : (y) );}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
int IntegerBmin(int x,int y) {return ((x) < (y) ? (x) : (y) );}

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
int IntegerBmax(int x,int y) {return ((x) > (y) ? (x) : (y) );}

#define IfThenElse(c, x, y) \
  (c ? x : y)

#define signum(x) ( ((x)>0.0) ? 1.0 : ((x)<0.0) ? -1.0 : 0.0 )

#define arctan(x) atan(x)

#define arctan2(y,x) atan2(y,x)

#define NoEvaluate(x) (x)

#define NoEvent(x) (x)

#if __GNUC__
static double tanh__(double x) {
	return fabs(x)<1e2 ? (tanh)(x) : signum(x);
}
#define tanh(x) tanh__(x)
#endif

/* Pseudo-random number generators for Dymosim.
 *
 * RandomUniform(time)   Uniformly distributed random number,
 *                       range [0, 1].
 *
 * RandomNormal(time)    Normally distrubuted random number with
 *                       mean 0 and variance 1.
 *
 * RandomSeed(seed)      Initializes the random number generator.
 *
 * Note: the ANSI/ISO Standard C function rand() has alleged bad random
 * properties in many implementations.  For that reason, we use random()
 * when possible.
 *
 */

#if defined(SUN) || defined(HAS_RANDOM)
#define RandomUniform(time) ( (random() % 1000000) / 999999.0 )
#define RandomSeed(seed) (srandom((unsigned) seed), 0)
#else
#define RandomUniform(time) ( (double) rand() / (double) RAND_MAX )
#define RandomSeed(seed) (srand((unsigned) seed), 0)
#endif

static double RandomNormal(double time)
{
  int i;
  double r = -6;
  for (i = 0; i < 12; i++) r += RandomUniform(time);
  return r;
}

static double log_variable(char *xname, double t, double x) {
#if !defined(DynSimStruct)
  char buf[500];
  sprintf(buf, "%.400s(%g) = %.16g", xname, t, x);
  DymosimMessage(buf);
#elif defined(RTLAB)
  OpalPrint("%s(%g) = %.16g\n", xname, t, x);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
  ssPrintf("%s(%g) = %.16g\n", xname, t, x);
#else
  printf("%s(%g) = %.16g\n", xname, t, x);
#endif
  return x;
}

#define LogVariable(x) \
  log_variable(#x, DymosimGetTime2(), x)

DYMOLA_STATIC double PackShape(char * shapename)
{
  if (strcmp(shapename, "box") == 0)
    return 101.0;
  else if (strcmp(shapename, "sphere") == 0)
    return 102.0;
  else if (strcmp(shapename, "cylinder") == 0)
    return 103.0;
  else if (strcmp(shapename, "cone") == 0)
    return 104.0;
  else if (strcmp(shapename, "pipe") == 0)
    return 105.0;
  else if (strcmp(shapename, "beam") == 0)
    return 106.0;
  else if (strcmp(shapename, "wirebox") == 0)
    return 107.0;
  else if (strcmp(shapename, "gearwheel") == 0)
    return 108.0;
  else if (strcmp(shapename, "vector") == 0)
	return 109.0;
  else if (strcmp(shapename, "pipecylinder") == 0)
	return 110.0;
  else if (strcmp(shapename, "spring") == 0)
	  return 111.0;
  else if (strcmp(shapename, "tire")==0 || strcmp(shapename,"tyre")==0) 
	  return 112.0;
  else {
    return 200.0+atoi(shapename);
  }
}

DYMOLA_STATIC double PackMaterial(double d1, double d2, double d3, double d4)
{
    int a, b, c, d, ires;
    double res;

    /* Pack arguments in the range 0.00-1.00 and scale to 0-99. */

    a = (int) (d1*100 - 0.5);
    if (a < 0) a = 0;
    if (a > 99) a = 99;

    b = (int) (d2*100 - 0.5);
    if (b < 0) b = 0;
    if (b > 99) b = 99;

    c = (int) (d3*100 - 0.5);
    if (c < 0) c = 0;
    if (c > 99) c = 99;

    d = (int) (d4*10 - 0.5);
    if (d < 0) d = 0;
    if (d > 9) d = 9;

    /* Construct large integer packing arguments */

    ires = ((((a * 100) + b) * 100) + c) * 10 + d;
    
    res = ires;
    return res;
}

/* Event handling */
LIBDS_API void handleevent3(const char *, int *, double *, 
	    double *, double , Dymola_bool , int , double , 
	    double , Dymola_bool *, Dymola_bool eventiter, double largeeps, Dymola_bool slow);

LIBDS_API int booleanchanged_(const char *, Dymola_bool *,
	    Dymola_bool *, int *, Dymola_bool *, int);


#if 1
#define HandleEvent(cross,expr,index) \
    QRel_[index-1] = cross; \
    if (DYNEvent) { \
	handleevent3(expr, &QM_[index], &Qp_[index-1], &Qn_[index-1], QRel_[index-1], \
		Init_, PrintEvent, EPS_, *time, &AnyEvent_, Qenable_[index], LargeEPS_, Iter>SlowIter_); \
    } \
    if (RootFinder_) { \
      (DSE_STRUCT QZ_)[2*index-2] = QRel_[index-1] - Qp_[index-1]; \
      (DSE_STRUCT QZ_)[2*index-1] = QRel_[index-1] - Qn_[index-1]; \
    }
#else
#define HandleEvent(cross,expr,index) \
    QRel_[index-1] = cross; \
    if (DYNEvent) { \
	handleevent_(expr, &QM_[index], &Qp_[index-1], &Qn_[index-1], &QRel_[index-1], \
		&Init_, &PrintEvent, &EPS_, time, &AnyEvent_, strlen(expr)); \
    } \
    if (RootFinder_) { \
      QZ_[2*index-2] = QRel_[index-1] - Qp_[index-1]; \
      QZ_[2*index-1] = QRel_[index-1] - Qn_[index-1]; \
    }
#endif


LIBDS_API void handleevent4(const char*rele,const char*sube,Dymola_bool*ql,double*qp,double*qn,double eps,double qrel,Dymola_bool init,int printevent,
			 Dymola_bool*anyevent,Dymola_bool ltz,Dymola_bool invres,Dymola_bool eventiter,double largeeps,Dymola_bool slow);
LIBDS_API void handleevent5(const char*rele,const char*sube,Dymola_bool*ql,double*qp,double*qn,double eps,double qrel,Dymola_bool init,int printevent,
			 Dymola_bool*anyevent,Dymola_bool*anyEvent2,Dymola_bool ltz,Dymola_bool invres,Dymola_bool eventiter,double largeeps,Dymola_bool slow);

#define HandleEvent2A(cross,xexpr,rel,yexpr,index,ltz,invres) \
    ((QRel_[index-1] = cross, \
    ((DYNEvent) ? \
    (handleevent4(xexpr " " rel " " yexpr,"(" xexpr ")-(" yexpr ")",&QL_[index], &Qp_[index-1],&Qn_[index-1],EPS_*Qscaled_[index-1],QRel_[index-1],Init_, PrintEvent,&AnyEvent_,ltz,invres,Qenable_[index],LargeEPS_*Qscaled_[index-1],Iter>SlowIter_),0):0), \
      (DSE_STRUCT QZ_)[2*(index)-2] = QRel_[index-1] - Qp_[index-1], \
      (DSE_STRUCT QZ_)[2*(index)-1] = (DSE_STRUCT QZ_)[2*(index)-2]),Qenable_[index]=true,QL_[index])

#define HandleEvent2(cross,xexpr,rel,yexpr,index,ltz,invres) \
    ((DYNX(QRel_,index-1) = cross, \
    ((DYNEvent) ? \
    (handleevent4func(did_,xexpr " " rel " " yexpr,"(" xexpr ")-(" yexpr ")",index,PrintEvent,ltz,invres),0):0), \
      DYNX((DSE_STRUCT QZ_),2*(index)-2) = DYNX(QRel_,index-1) - DYNX(Qp_,index-1), \
      DYNX((DSE_STRUCT QZ_),2*(index)-1) = DYNX((DSE_STRUCT QZ_),2*(index)-2)),DYNX(Qenable_,index)=true,DYNX(QL_,index))

#define HandleEvent2Minor(cross,xexpr,rel,yexpr,index,ltz,invres) \
    ((DYNX(QRel_,index-1) = cross, \
    ((DYNEvent) ? \
    (handleevent4funcMinor(did_,xexpr " " rel " " yexpr,"(" xexpr ")-(" yexpr ")",index,PrintEvent,ltz,invres),0):0), \
      DYNX((DSE_STRUCT QZ_),2*(index)-2) = DYNX(QRel_,index-1) - DYNX(Qp_,index-1), \
      DYNX((DSE_STRUCT QZ_),2*(index)-1) = DYNX((DSE_STRUCT QZ_),2*(index)-2)),DYNX(Qenable_,index)=true,DYNX(QL_,index))

LIBDS_API Dymola_bool handleevent4S(const char*rele,const char*sube,Dymola_bool*ql,double*qp,double*qn,double eps,double qrel,double*qz,Dymola_bool init,Dymola_bool ev,Dymola_bool i4,int printevent,Dymola_bool*anyevent,Dymola_bool ltz,Dymola_bool invres,Dymola_bool*eventiter,double largeeps,Dymola_bool slow,double t);

#define HandleEvent2S(cross,xexpr,rel,yexpr,index,ltz,invres) \
	(DYNX(QRel_,index-1)=(cross),\
	(handleevent4Sfunc(did_,xexpr " " rel " " yexpr,"(" xexpr ") - (" yexpr ")",(DSE_STRUCT QZ_),index,*(DSE_STRUCT idemand_)==4,DYNTime,PrintEvent,ltz,invres)))

static double round0(double x) {
	return (x>0) ? floor(x) : ceil(x);
}
LIBDS_API void roundEvent4(const char*expr,double (*func)(double),double qrel,double*res,
				 double*fuzz,double epsil,
						int posi,int negi,int reli,
						int init,int printevent,int *anyevent,int eventiter,double LargeEPS,int slow);

#define roundEvent(cross,func,expr,index,posi,negi,reli) \
	( DYNX(QRel_,index-1) = cross,\
		(DYNEvent? (roundEvent4(expr,func,DYNX(QRel_,index-1),&DYNX(Qp_,index-1),&DYNX(Qn_,index-1),EPS_,\
		posi,negi,reli,Init_,PrintEvent,&AnyEvent_,DYNX(Qenable_,index),LargeEPS_,Iter>SlowIter_),0):0),\
		DYNX((DSE_STRUCT QZ_),2*(index)-2) = -(DYNX(QRel_,index-1)-DYNX(Qp_,index-1)+DYNX(Qn_,index-1)+((posi)?(reli?(DYNX(Qp_,index-1)<=0):1):0)),\
		DYNX((DSE_STRUCT QZ_),2*(index)-1) = -(DYNX(QRel_,index-1)-DYNX(Qp_,index-1)-DYNX(Qn_,index-1)-((negi)?(reli?(DYNX(Qp_,index-1)>=0):1):0)),\
		DYNX(Qenable_,index)=true,DYNX(Qp_,index-1))

#define floorEvent(cross,xexpr,index) \
	roundEvent(cross,floor,"floor(" xexpr ")",index+1,0,1,0)

#define ceilEvent(cross,xexpr,index) \
	roundEvent(cross,ceil,"ceil(" xexpr ")",index+1,1,0,0)

#define divideDymolaEvent(x,xexpr,y,yexpr,index) \
	roundEvent(((double)(x))/(y),round0,"div(" xexpr "," yexpr ")",index+1,1,1,1)

#define real2integerEvent(cross,xexpr,index) \
	real2integer(roundEvent(cross,floor,"integer( " xexpr ")",index+1,0,1,0))

#define remainderDymolaEvent(x,xexpr,y,yexpr,index) \
	((x)-(y)*divideDymolaEvent(x,xexpr,y,yexpr,index))

#define modulusDymolaEvent(x,xexpr,y,yexpr,index) \
	((x)-(y)*roundEvent(((double)(x))/(y),floor,"floor(" xexpr "/" yexpr ")",index+1,0,1,0))

#define BooleanChanged(name,state,new) \
      {Dymola_bool b1_,b2;\
	  b1_ = (Dymola_bool) state; \
      b2_ = (Dymola_bool) new; \
      booleanchanged_(name, &b1_, &b2_, &PrintEvent, &AnyEvent_, strlen(name)); \
	  state = new;}

#define cross_(exprnr) \
    (DYNX(Qenable_,exprnr)=true, DYNX(QL_,exprnr))

#define when(cond,index) \
	if (Init_) DYNX(QEvaluate_,index) = true;\
	if (cond) { \
		if (DYNX(QEvaluate_,index) && (DYNEvent)) {AnyEvent_=true;DYNX(QEvaluate_,index)=false;

#define endwhen(index) \
     } \
   } else {\
     if (!DYNX(QEvaluate_,index)) { DYNX(QEvaluate_,index) = true;if (DYNEvent) AnyEvent_=true;}}

#define whenModelica(cond,index) \
   if (Init_)  {Init_=2;\
  	 DYNX(QEvaluateNew_,index) = DYNX(QEvaluate_,index) = !(cond); \
	 Init_=1;\
   }\
   if (!(cond)) { \
	 if (!DYNX(QEvaluate_,index)) { DYNX(QEvaluateNew_,index) = true;/*if (DYNEvent) AnyEvent_=true;*/}\
   } else { \
	 if (DYNX(QEvaluate_,index) && (DYNEvent)) {AnyEvent_=true;DYNX(QEvaluateNew_,index) = false;\
		if (!haveDoneWhen_) {haveDoneWhen_=1;

#define whenModelicaOld(cond,index) \
   if (Init_)  {\
  	 DYNX(QEvaluateNew_,index) = DYNX(QEvaluate_,index) = true; \
   }\
   if (!(cond)) { \
	 if (!DYNX(QEvaluate_,index)) { DYNX(QEvaluateNew_,index) = true;/*if (DYNEvent) AnyEvent_=true;*/}\
   } else {\
	 if (DYNX(QEvaluate_,index) && (DYNEvent)) {AnyEvent_=true;DYNX(QEvaluateNew_,index) = false;\
		if (!haveDoneWhen_) {haveDoneWhen_=1;
     
#define endwhenModelica() \
		}\
     } \
   }
     

#define whenModelicaS(cond) \
	if (cond && !haveDoneWhen_) {{{haveDoneWhen_=1;

#define vectorWhen(cond,index,nrIndex) \
   if (Init_) {\
    IntegerArray a_;int i_;\
    Init_=2;a_=cond;Init_=1;\
	for(i_=0;i_<nrIndex;i_++) QEvaluateNew_[index+i_]=QEvaluate_[index+i_]=!a_.data[i_];\
    Release();} \
   if (VectorWhenHandle(cond,IntegerTemporaryDenseOrig(QEvaluate_+index,1,nrIndex),IntegerTemporaryDenseOrig(QEvaluateNew_+index,1,nrIndex),DYNEvent,&AnyEvent_)) {\
	if (!haveDoneWhen_) {haveDoneWhen_=1;

#define vectorWhenOld(cond,index,nrIndex) \
   if (Init_) {\
    int i_;\
	for(i_=0;i_<nrIndex;i_++) QEvaluateNew_[index+i_]=QEvaluate_[index+i_]=true;\
   } \
   if (VectorWhenHandle(cond,IntegerTemporaryDenseOrig(QEvaluate_+index,1,nrIndex),IntegerTemporaryDenseOrig(QEvaluateNew_+index,1,nrIndex),DYNEvent,&AnyEvent_)) {\
	if (!haveDoneWhen_) {haveDoneWhen_=1;

#define endVectorWhen() }}

#define beginwhenBlock {int haveDoneWhen_=0;
#define endwhenBlock }

#define UpdateQEvaluate(whenindex)\
	if (DYNEvent&&(final_&&(DymolaOneIteration_==0||DymolaOneIteration_==4) || (!final_&&(DymolaOneIteration_==3||DymolaOneIteration_==4)))) {int i_;for (i_ = 0; i_ < whenindex;i_++) {QEvaluate_[i_]=QEvaluateNew_[i_];}}\
	if (DYNEvent&&!final_) {int i_;for (i_ = 0; i_ < whenindex;i_++) {QEvaluateNew_[i_]=QEvaluate_[i_];}}\

#define UpdateSampleCounters(sampleindex) \
	if (DYNEvent&&(final_&&(DymolaOneIteration_==0||DymolaOneIteration_==4) || (!final_&&(DymolaOneIteration_==3||DymolaOneIteration_==4)))) {int i_;for (i_=0;i_<sampleindex;i_++) {NextSampleTime_[i_]=NextSampleTimeNew_[i_];NextSampleAct_[i_]=NextSampleActNew_[i_];}}
     
#define Initial(v) \
  (Init_)

     
#define initialAlsoContinue() ((Init_==1)?(AnyEvent_=1):0)
#ifdef DymolaOldInitialForContinue_
#define initial() initialAlsoContinue()
#else
#define initial() (((Init_==1) && !continueSimulate_)?(AnyEvent_=1):0)
#endif

#define Terminal(v) \
  (*idemand_ == 7)

#define terminal() (*idemand_ == 7)


#define SecondDegree 1


#define currentStepSizeRatio2_ (((struct BasicDDymosimStruct*)(DSE_STRUCT duser_))->mCurrentStepSizeRatio2)
#define NextTimeEvent (((struct BasicDDymosimStruct*)(DSE_STRUCT duser_))->mNextTimeEvent)
DYMOLA_STATIC void CheckForEvents(struct DYNInstanceData*did_,double Time, int Init, int Event, 
       double QZ_[], int nrel_, double F_[], int nx_,double*duser_,int*iuser_);



/* Special operators that allows multiple assignments.
   Used for Petri net library. */

#define SetBoolean2(var1, val1, var2, val2) \
  0.0; \
  BooleanChanged(#var1, var1, val1); \
  BooleanChanged(#var2, var2, val2); \
  var1 = val1; \
  var2 = val2; \
  if ( Iter < MaxIter) { \
     if (PrintEvent&(1<<1)) \
        DymosimMessage("Iterating to find consistent restart conditions."); \
     PerformIteration_ = true; \
     goto finish; \
  }

#define SetBoolean3(var1, val1, var2, val2, var3, val3) \
  0.0; \
  BooleanChanged(#var1, var1, val1); \
  BooleanChanged(#var2, var2, val2); \
  BooleanChanged(#var3, var3, val3); \
  var1 = val1; \
  var2 = val2; \
  var3 = val3; \
  if ( Iter < MaxIter) { \
     if (PrintEvent&(1<<1)) \
        DymosimMessage("Iterating to find consistent restart conditions."); \
     PerformIteration_ = true; \
     goto finish; \
  }

#define BreakDeclareFunctionDef(nr) \
	DYMOLA_STATIC void declare_##nr(double x0_[], double dp_[], double du_[], int *QiErr); \

 #define BreakDeclareFunction(nr) \
    {     BreakDeclareFunctionDef(nr) declare_##nr(x0_, dp_, QiErr);  \
    } \
  } \
    \
  DYMOLA_STATIC void declare_##nr(double x0_[], double dp_[], double du_[], int *QiErr) \
  { 

#define BreakDeclareFunctionNew(nr) \
    {     declare_##nr(x0_, dp_, du_, QiErr);  \
    } \
  } \
    \
  DYMOLA_STATIC void declare_##nr(double x0_[], double dp_[], double du_[], int *QiErr) \
  { 


#define BreakEquationsFunction(nr) \
    {  equations_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_, did_, \
      QiErr); \
    } \
  finish: \
  leave: \
  if (GlobalError_ != 0) \
    *QiErr = GlobalError_; \
  } \
    \
  DYMOLA_STATIC void equations_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_, \
      int *QiErr) \
  { \
  if (PerformIteration_ || (*QiErr != 0 && *QiErr != -999)) \
    DYN_GOTOFINISH;
 
#define BreakSectionFunctionDef(nr) \
	DYMOLA_STATIC void equations_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_, \
      int *QiErr); 

#define BreakSectionFunction(nr) \
    }\
    { BreakSectionFunctionDef(nr) \
    equations_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_, did_, \
      QiErr); \
    } \
  finish: \
  leave: \
  if (GlobalError_ != 0) \
    *QiErr = GlobalError_; \
  } \
    \
  DYMOLA_STATIC void equations_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_, \
      int *QiErr) \
  { \
  if (PerformIteration_ || (*QiErr != 0 && *QiErr != -999)) \
    DYN_GOTOFINISH;\
  if (sectioncondition) {

#define BreakSectionFunctionNew(nr) \
    }\
    { \
    equations_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_, did_, \
      QiErr); \
    } \
  finish: \
  leave: \
  if (GlobalError_ != 0) \
    *QiErr = GlobalError_; \
  } \
    \
  DYMOLA_STATIC void equations_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_, \
      int *QiErr) \
  { \
  if (PerformIteration_ || (*QiErr != 0 && *QiErr != -999)) \
    DYN_GOTOFINISH;\
  if (sectioncondition) {


#define BreakSectionFunctionCallNew(nr) \
  } { \
    equations_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_, did_, \
      QiErr); \
    } if (sectioncondition) {

#define BreakSectionFunctionEnd() \
  } \
  finish: \
  leave: \
  if (GlobalError_ != 0) \
    *QiErr = GlobalError_; \
  }

#define BreakSectionFunctionStart(nr) \
  DYMOLA_STATIC void equations_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
      int *QiErr) \
  { \
  if (PerformIteration_ || (*QiErr != 0 && *QiErr != -999)) \
    DYN_GOTOFINISH;\
  if (sectioncondition) {

#if (defined(_OPENMP) && !defined(DISABLE_DYMOLA_OPENMP))
#define DYN_GOTOLEAVE 
#define DYN_GOTOFINISH
#else
#define DYN_GOTOLEAVE goto leave
#define DYN_GOTOFINISH goto finish
#endif


#define BreakSectionJacDef(nr) \
	DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	   int *QiErr,double*Jacobian____internal,int Jacobian____m);

#define BreakSectionJacCallNew(nr) \
   { switch(equationsJ_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_,did_, \
      QiErr,Jacobian____internal,Jacobian____m)) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionJacCall(nr) \
   { BreakSectionJacDef(nr) switch(equationsJ_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_,did_, \
      QiErr,Jacobian____internal,Jacobian____m)) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionJacEnd() \
	   return 0;finish: return 1;leave:return 2;}

#define BreakSectionJacStart(nr) \
	   DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	   int *QiErr,double*Jacobian____internal,int Jacobian____m) {

#define BreakSectionODEJacStart(nr) \
	   DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	   int *QiErr) {

#define BreakSectionODEJacDef(nr) \
    DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	   int *QiErr);

#define BreakSectionODEJacCall(nr) \
   { BreakSectionODEJacDef(nr) switch(equationsJ_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_,did_, \
      QiErr)) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionODEJacCallNew(nr) \
   { switch(equationsJ_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_,did_, \
      QiErr)) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionODEJacEnd() \
	   return 0;finish: return 1;leave:return 2;}

#define BreakSectionDef(nr) \
   DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_, \
	   int *QiErr);

#define BreakSectionCallNew(nr) \
   { switch(equationsJ_##nr((DSE_STRUCT idemand_), (DSE_STRUCT icall_), \
      time, (DSE_STRUCT X_), (DSE_STRUCT XD_), (DSE_STRUCT U_), \
      (DSE_STRUCT DP_), (DSE_STRUCT IP_), (DSE_STRUCT LP_), \
      (DSE_STRUCT F_), (DSE_STRUCT Y_), (DSE_STRUCT W_), (DSE_STRUCT QZ_), \
      (DSE_STRUCT duser_), (DSE_STRUCT iuser_), (DSE_STRUCT cuser_), (DSE_STRUCT did_), \
      (DSE_STRUCT QiErr))) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionCall(nr) \
   { BreakSectionDef(nr) \
     switch(equationsJ_##nr(idemand_, icall_, \
      time, X_, XD_, U_, \
      DP_, IP_, LP_, \
      F_, Y_, W_, QZ_, \
      duser_, iuser_, cuser_, did_, \
      QiErr)) { case 1:DYN_GOTOFINISH;case 2:DYN_GOTOLEAVE;default:;} \
	}

#define BreakSectionEnd() \
	   return 0;finish: return 1;leave:return 2;}

#define BreakSectionStart(nr) \
	   DYMOLA_STATIC int equationsJ_##nr(int *idemand_, int *icall_, \
      double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	   int *QiErr) {

#define StartPreBlock if ((Init_||DYNEvent ||DymolaOneIteration_==5) && (final_!=2 || DymolaOneIteration_==2 || DymolaOneIteration_ == 0) ) {

#define EndPreBlock if (!final_ && (DymolaOneIteration_==3) && (PrintEvent&(1<<1))) DymosimMessage("Iterating to find consistent restart conditions.");}

#define BreakPreBlockDef(nr) DYMOLA_STATIC void initializeDataPre##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	int final_,int solverCall);

#define BreakPreBlockNew(nr) EndPreBlock \
   { initializeDataPre##nr(time,X_,XD_,U_,DP_,IP_,LP_,F_,Y_,W_,QZ_,duser_,iuser_,cuser_,did_,final_, solverCall);}} \
	DYMOLA_STATIC void initializeDataPre##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],struct DYNInstanceData*did_, \
	int final_,int solverCall) {StartPreBlock

#define BreakPreBlock(nr) EndPreBlock \
   { BreakPreBlockDef(nr) \
	initializeDataPre##nr(time,X_,XD_,U_,DP_,IP_,LP_,F_,Y_,W_,QZ_,duser_,iuser_,cuser_,did_,final_, solverCall);}} \
	DYMOLA_STATIC void initializeDataPre##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_,\
	int final_,int solverCall) {StartPreBlock


#define EndEqBlock }

#define BreakEquBlockDef(nr) DYMOLA_STATIC void initializeDataEqu##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_,\
	int final_,int solverCall);

#define BreakEquBlockNew(nr) EndEqBlock \
   { initializeDataEqu##nr(time,X_,XD_,U_,DP_,IP_,LP_,F_,Y_,W_,QZ_,duser_,iuser_,cuser_,did_,final_, solverCall);}} \
	DYMOLA_STATIC void initializeDataEqu##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_,  double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[], struct DYNInstanceData*did_,\
	int final_,int solverCall) {StartEqBlock

#define BreakEquBlock(nr) EndEqBlock \
   { BreakEquBlockDef(nr) \
	initializeDataEqu##nr(time,X_,XD_,U_,DP_,IP_,LP_,F_,Y_,W_,QZ_,duser_,iuser_,cuser_,final_, solverCall);}} \
	DYMOLA_STATIC void initializeDataEqu##nr(double *time, double* X_, double* XD_, double* U_, \
      double* DP_, int IP_[], Dymola_bool LP_[], \
      double* F_, double* Y_, double* W_, double QZ_[], \
      double duser_[], int iuser_[], void*cuser_[],did_, \
	int final_,int solverCall) {StartEqBlock

#define EndDataBlock }

#define AssertEquation(expr1, expr2) \
  if(fabs((expr1) - (expr2)) > 1E-6) \
    DymosimMessageDouble("ERROR: " #expr1 " - (" #expr2 ")NOT EQUAL TO ZERO: ", (expr1) - (expr2))


/* Routines to implement memory block. 

   The putMemory function saves its input in a memory area at
   output points. The getMemory function retrieves the value.
   By use of these functions it is possible to break dependency
   loops.

   Note that memory vector needs to have 2 elements.

   Warning: The memory functions should be used with care since 
   it is possible to introduce errors that the integration routine
   can not handle.
*/


DYMOLA_STATIC double getMemory(double memory[], int n1, int n2) {
  if (n1 == 1 && n2 == 1) 
    return DymosimError("Memory argument to getMemory must be a vector.");
    
  return memory[0];
}

DYMOLA_STATIC double putMemoryCond(int cond, double memory[], int n1, int n2, double u) {
  if (n1 == 1 && n2 == 1) 
    return DymosimError("Memory argument to putMemory must be a vector.");

  if (cond)
    memory[0] = u;
  return 0;
}

#define putMemory(memory, n1, n2, u) \
  putMemoryCond(*idemand_ == 3, memory, n1, n2, u)

#define putMemoryAtEvent(memory, n1, n2, u) \
  putMemoryCond(Event, memory, n1, n2, u)


DYMOLA_STATIC void registerTimeEventNew(const double atTime,struct DYNInstanceData*did_);
DYMOLA_STATIC void registerTimeEvent(const double atTime);
static double findCounter(double Time,double start,double interval) {
  double i=ceil((Time-start)/interval);
  return i+1;
}
DYMOLA_STATIC const char* dymosimResources(void);
DYMOLA_STATIC Dymola_bool sampleFunctionM(struct DYNInstanceData*did_,double Time, double start, double interval, int counter,
                      Dymola_bool Init, Dymola_bool Event);
DYMOLA_STATIC Dymola_bool sampleFunctionM3(struct DYNInstanceData*did_,double Time, double start, double interval, int phase, int maxVal, int counter,
                      Dymola_bool Init, Dymola_bool Event);

/* Special cases for Timed events */

#define GreaterEqualTime(y, nr) \
  (((Init_||DYNEvent) && ( \
  (DYNTime<y-(4e-14)*(fabs(DYNTime)+(((struct BasicDDymosimStruct*)(DSE_STRUCT duser_))->mOrigTimeError))) ? registerTimeEventNew(y,did_),(DYNX(QTimed_,nr)=0):(DYNX(QTimed_,nr)?0:(AnyDEvent_=DYNX(QTimed_,nr)=1,(DymolaOneIteration_!=0)?AnyEvent_=1:1)))),DYNX(QTimed_,nr))
/* Deactivate the state event */

#define GreaterEqualTimeMinor(y, nr) \
  (((Init_||DYNEvent) && ( \
  (DYNTime<y-(4e-14)*(fabs(DYNTime)+(((struct BasicDDymosimStruct*)(DSE_STRUCT duser_))->mOrigTimeError))) ? registerTimeEventNew(y,did_),(DYNX(QTimed_,nr)=0):((((DYNX(QTimed_,nr)==0&&DymolaOneIteration_!=0)?AnyEvent_=true:true),DYNX(QTimed_,nr)=1)))),DYNX(QTimed_,nr))
/* Deactivate the state event */

#define LessTime(y, nr) (!GreaterEqualTime(y,nr))
#define LessTimeMinor(y, nr) (!GreaterEqualTimeMinor(y,nr))

#define Sample(start, interval, SampleCounter) \
    (DYNEvent ? sampleFunction(did_, DYNTime, start, interval, SampleCounter, Init_, DYNEvent) : 0.0) 
/*    (Event ? sampleFunction1(Time, start, interval) : 0.0) */

/* For Modelica */
#define sample(start, interval, SampleCounter) \
    (DYNEvent ? sampleFunctionM(did_, DYNTime, start, interval, SampleCounter, Init_, DYNEvent) : 0.0)

#define sampleNew(start, interval, SampleCounter) \
	(Init_ ? (AnyEvent_=true,0.0) : sample(start, interval, SampleCounter) ? ((DymolaOneIteration_!=0)?(AnyEvent_=true):true) : false)

#define sampleNew2(start, interval, SampleCounter) \
	(Init_ ? (AnyEvent_=true,0.0) : (sample(start, interval, SampleCounter) ? (AnyEvent_=true) : false))

#define sampleNew3(start, interval, phase, maxVal, SampleCounter) \
	(Init_ ? (AnyEvent_=true,0.0) : ((DYNEvent ? sampleFunctionM3(did_, DYNTime, start, interval, phase, maxVal, SampleCounter,Init_,DYNEvent):0.0) ? (AnyEvent_=true) : false))

#define StepSizeCalculations(iv)\
	ResetIfNewSimulation(StepSize=0;previousTime_,-1e30,iv);\
    if (previousTime_<0) {previousTime_=DYNTime;currentStepSize_=0;}\
    else if (DYNTime == previousTime_ || DYNEvent) {currentStepSize_ = 0;previousTime_=DYNTime;}\
    else if (DYNFindEvent) {previousTime_ = DYNTime;} else {currentStepSize_=DYNTime-previousTime_;previousTime_ = DYNTime;}\
    if (DYNFindEvent && StepSize == 0 && DYNTime > LastTime) {\
     StepSize = DYNTime - LastTime;\
     currentStepSize_ = StepSize;\
    }
    /* Special case since the currentStepSize_ is computed inside CheckForEvents */
    /* and only reset to zero here */

#define whenModelicaS3(iv,prev1,curr1,cond1)\
	ResetIfNewSimulation(prev1,-1e30,iv);\
	whenModelicaS(((cond1) || Init_ || (DYNEvent && prev1==DYNTime))) \
    if (prev1==DYNTime || prev1<-1e29) curr1=0;else curr1=DYNTime-prev1;prev1=DYNTime;currentStepSize_=curr1;

#define whenModelicaS2(iv,prev1,curr1,cond1,samp)\
	ResetIfNewSimulation(prev1,-1e30,iv);\
	whenModelicaS(((cond1) || Init_ || (DYNEvent && prev1==DYNTime))) \
    if (prev1==DYNTime || prev1<-1e29) curr1=0;else curr1=samp;prev1=DYNTime;currentStepSize_=curr1;

#define BeginStepSizeCalculations(iv,prev1,curr1,cond1,samp)\
    beginwhenBlock\
	whenModelicaS2(iv,prev1,curr1,cond1,samp)

#define EndStepSizeCalculations()\
	endwhenModelica()\
	endwhenBlock

#define ResetIfNewStep(v,val,resetOldTime_,oldResetCnt_) \
	{ if ((resetOldTime_!=DYNTime)||(oldResetCnt_!=ResetCounter_)) {v=val;resetOldTime_=DYNTime;oldResetCnt_=ResetCounter_;}}

#define ResetIfNewSimulation(v,val,oldResetCnt_) \
	{ if ((oldResetCnt_!=ResetCounter_)) {v=val;oldResetCnt_=ResetCounter_;}}

	static double CheckContinuousIfCode(int c,const char*ys,double*v,double newValue,double Time,double InitTime) {
		if (c && fabs(*v-newValue)>1e-3*(1+fabs(newValue)+fabs(*v)) && Time!=InitTime) {
#if defined(DYMOSIM)
			char buf[1000];
			sprintf(buf, "\nModel error - differentiated if-then-else was not continuous:\n %s\n Value jumped from %g to %g.\n", ys, *v, newValue);
			DymosimError(buf);
#elif defined(Matlab6) && !defined(NO_FILE) && defined(ssPrintf)
              if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
	            ssPrintf("\nModel error - differentiated if-then-else was not continuous:\n %s\n Value jumped from %g to %g.\n", ys, *v, newValue);
			  }
			DymosimError("Model error - differentiated if-then-else was not continuous");
#else
            if (!(getBasicIDymosimStruct()->mPrintEvent&(1<<10))) {
			  printf("\nModel error - differentiated if-then-else was not continuous:\n %s\n Value jumped from %g to %g.\n", ys, *v, newValue);
			}
			DymosimError("Model error - differentiated if-then-else was not continuous");
#endif
		}
		return *v=newValue;
	}

#if DymolaNoGuard_
#define CheckContinuousIf(c,ys,nr) (c)
#else
#define CheckContinuousIf(c,ys,nr)\
	(CheckContinuousIfCode(DYNEvent&&Iter>0&&!Init_,ys,QCheckIf_+nr,c,DYNTime,InitTime))
#endif
    
/* Solution of linear systems of equations. */

LIBDS_API int dymres_(double* a, const int* lda, const int* n, double* b, int* ierr);

LIBDS_API  int dymli1_(int* sysnr, const int *fact, double* a, int* lda, int* n, 
                   double* b, double *Time, int* Event, int* PrintEvent,
                   double* dwork, int* iwork, int* ierr);

LIBDS_API int dymli2_(int* sysnr, int *fact, double *a, int* lda, int *n,
		   double* b, double *Time, int *Event, int* PrintEvent,
		   double* dwork, int* iwork, int *factor, int* ierr);

LIBDS_API  int dymli3_(int* sysnr, int *fact, double *a, int* lda, int *n,
		   double* b, double *Time, int *Event, int* PrintEvent,
		   double* dwork, int* iwork, int *factor, const char*const*varnames,int* ierr);

LIBDS_API  int dymli4_(int* sysnr, int *fact, double *a, int* lda, int *n,
		   double* b, double *Time, int *Event, int* PrintEvent,
		   double* dwork, int* iwork, int *factor, const char*const*varnames,int* ierr,int*fEvent);

LIBDS_API  int dymli5_(int* sysnr, int *fact, double *a, int* lda, int *n,
		   double* b, const double*x0, double *Time, int *Event, int* PrintEvent,
		   double* dwork, int* iwork, int *factor, const char*const*varnames,int* ierr,int*fEvent);


LIBDS_API  int dymlin_(int* infrev, int* n, double* sol, double* res, double *jac,
                   int* ljac, double* dwork, int *iwork, double *Time,
                   int* event, int *printpriority, int *sysnr, int *ierr);

LIBDS_API  int dymnon_(
	int *qinfrev, int *qiopt, int *qnnl,
	double *qsol, double *qres, double *qjac, double *qtol,
	int *qinfo,
	double *qd,
	int *qi, int *printevent, int *qnlnr,
	double *time,
	int *qnlfunc, int *qnljac, int *qnlmax, int *ierr);

#define DymRes(A, Max, n, b, ierr_) \
    {int i1_,i2_;i1_ = MaxMat; \
    i2_ = n; \
	dymres_(qa_, &i1_, &i2_, qb_, ierr_);} 

#define DymSol(A, Max, n, b, Dwork, Iwork, ierr_) \
    if ( n > MaxMat ) { \
      DymosimMessage("The capacity for solving linear systems of equations, MaxMat, needs to be increased"); \
      goto leave; \
      } \
	  {int i1_,i2_,i3;i1_ = MaxMat;i2_ = n;i3_ = 0; \
	   dymli1_(&i3_, &i3_, qa_, &i1_, &i2_, qb_, &DYNTime, &Event, &PrintEvent, dwork_, iwork_, ierr_);}

#define DymLin(QInfRev,QiOpt,QNnl,QSol,QRes,QJac,Qtol,Qinfo,QD,QI, \
	PrintEvent,QNLnr,DYNTime,QNLfunc,QNLjac,QNLmax,ierr_) \
    if (QNnl > MaxMat) { \
      DymosimMessage("The capacity for solving linear systems of equations, MaxMat, needs to be increased"); \
      goto leave; \
      } \
	{int i1_,i2_,i3;i1_ = QMaxNonLin;i2_ = 0;i3_ = Event;\
	dymlin_(&QInfRev,&QNnl,QSol_,QRes_,QJac_,&i1_,dwork_,iwork_,&DYNTime,&i3_,&PrintEvent,&i2_,ierr_);}

#define QA_(i,j) \
    qa_[(j-1)*MaxMat + i-1]

#define Qb_(i) \
    qb_[i-1]


/* Solution of nonlinear systems of equations. */

#define QRes_(i) \
    QRes_[i-1]

#define QSol_(i) \
    QSol_[i-1]

#define QJac_(i,j) \
    QJac_[(j-1)*QNnl + i-1]

#define DymNon(QInfRev,QiOpt,QNnl,QSol,QRes,QJac,Qtol,Qinfo,QD,QI, \
	PrintEvent,QNLnr,DYNTime,QNLfunc,QNLjac,QNLmax,ierr_) \
    if (QNnl > QMaxNonLin) { \
      DymosimMessage("The capacity for solving nonlinear systems of equations, QMaxNonLin, needs to be increased"); \
      goto leave; \
      } \
    if (QNLnr > QNLmax) { \
      DymosimMessage("The capacity for solving nonlinear systems of equations, QNLmax, needs to be increased"); \
      goto leave; \
      } \
{int i1_,i2_;double Qtol2=Dymola_min(0.5*EPS_,Qtol*0.01);i1_ = QI_;i2_ = QNLmax;dymnon_(&QInfRev,&QiOpt,&QNnl,QSol_,QRes_,QJac_,&Qtol2,&Qinfo,QD_,&i1_, \
&PrintEvent,&QNLnr,DYNTime,QNLfunc,QNLjac,&i2_,ierr_);}

#define DymNeq(QInfRev_,QiOpt_,QSol_,QRes_,QJac_,Qinline_,Qtol_,Qinfo_, \
               QNLnr_,PrintEvent,DYNTime,QiErr) \
        dymNeq(&QInfRev_,&QiOpt_,QSol_,QRes_,QJac_,Qinline_,&Qtol_,&Qinfo_, \
               QNLnr_,PrintEvent,DYNTime,QiErr); \
        if ( Qinfo_ == -1 ) return 0;

#include <bloutil.h>
#ifdef _MSC_VER
#pragma warning ( disable : 4101 4102 )
#endif

#if defined(RT)
LIBDS_API double DymolaTimerCounterSince(double*d,int i) {
	if (i==0) {
		double x=0;
		if (d) *d=x;
		return x;
	} else {
		return 0-*d;
	}
}
#else
#include <time.h>
static const double invFreq=1.0/CLOCKS_PER_SEC;

typedef double (*timerCounterCBFunction)(double*,int);
timerCounterCBFunction DymolaTimerCounterCallback=0;

#ifndef BUILDFMU
#ifdef _MSC_VER
__declspec(dllexport)
#endif
void setTimerCounterCB(timerCounterCBFunction f)
{
  DymolaTimerCounterCallback = f;
}
#endif /* BUILDFMU */

LIBDS_API double myclock(void);
double DymolaTimerCounterSince(double*d,int i) {
	if (DymolaTimerCounterCallback)
		return DymolaTimerCounterCallback(d,i);
	if (i==0) {
		double x=myclock();
		if (d) *d=x;
		return x;
	} else {
		return invFreq*(myclock()-*d);
	}
}
#endif

#if defined(LIBDS_NODLL_API) || defined(LIBDS_DLL) 
void signalError(void) {
	DymosimError("");
}
	void (initializeData)(double *time, double* X_, double* XD_, double* U_, 
      double* DP_, int IP_[], Dymola_bool LP_[], 
      double* F_, double* Y_, double* W_, double QZ_[], 
      double duser_[], int iuser_[], void*cuser_[], 
      int final_,int Init,int m_Event,int solverCall);
	void (delayBuffersClose)(void);

DYMOLA_STATIC void SetDymolaJacobianPointers(struct DYNInstanceData*did_, double * QJacobian_,double * QBJacobian_,double * QCJacobian_,double * QDJacobian_,int QJacobianN_,
	int QJacobianNU_,int QJacobianNY_,double * QJacobianSparse_,int * QJacobianSparseR_,int * QJacobianSparseC_,int QJacobianNZ_);
DYMOLA_STATIC void SetDymolaJacobianPointers2(struct DYNInstanceData*did_, double * QJacobian_,double * QBJacobian_,double * QCJacobian_,double * QDJacobian_,int QJacobianN_,
	int QJacobianNU_,int QJacobianNY_,double * QJacobianSparse_,int * QJacobianSparseR_,int * QJacobianSparseC_,int QJacobianNZ_,int *QJacobianABCDNZ_); 
/* If QJacobianABCDNZ_ is non-null it _receives_ the number of non-zero elements in the sparse ABCD. If additionally QJacobianSparse_ is non-null it activates sparse ABCD-matrix */
struct DymolaTimes;
struct DymolaTimes* GetDymolaTimers(struct DYNInstanceData*, int*);
#if defined(LIBDS_DLL)
__declspec(dllexport) 
#endif
	const struct DymosimModel* DymosimModelFunctions(void) {
	extern const char*modelName;
    extern const char* usedLibraries[];
	extern const char*dllLibraryPath[];
	extern const char*default_dymosim_license_filename;
	extern int QJacobianCG_[];
	extern int QJacobianGC_[];
	extern double QJacobianCD_[];

	static struct DymosimModel a={
		12,
		registerTimeEvent,
		signalError,
		dsblock_,
		dsblockb_,
		GetDimensions2,
		initializeData,
		0,
		delayBuffersClose
	};
	a.modelName=modelName;
	a.usedLibraries=usedLibraries;
	a.dllLibraryPath=dllLibraryPath;
	a.default_dymosim_license_filename=default_dymosim_license_filename;
	a.QJacobianCG_=QJacobianCG_;
	a.QJacobianGC_=QJacobianGC_;
	a.QJacobianCD_=QJacobianCD_;
	a.QJacobian_=0;
	a.QJacobianN_=0;
	a.QJacobianNU_=0;
	a.QJacobianNY_=0;
	a.QJacobianSparse_=0;
	a.QJacobianSparseR_=0;
	a.QJacobianSparseC_=0;
	a.QJacobianNZ_=0;
	a.dymolaTimes_=0;
	a.dymolaTimersLen_=0;
	a.optFunctions=0;
	a.SetDymolaJacobianPointers=SetDymolaJacobianPointers;
	a.GetDymolaTimers=GetDymolaTimers;
	a.SetDymolaJacobianPointers2=SetDymolaJacobianPointers2;
#ifdef GODESS
	{
		extern struct SimulatorFunctions*GodessSimulatorFunctions();
		a.optFunctions=GodessSimulatorFunctions();
	}
#endif
	return &a;
}
#endif

#if defined(HACK_SUPPORT_VS2015)
#if defined(_MSC_VER) && _MSC_VER>=1900
/*
below is a stub for missing symbol in VS2015 UCRT used to return stdin/stdout/stderr pointers
due to changes in UCRT libraries stdin/stdout/stderr compiled with older VC versions can't be linked:
https://connect.microsoft.com/VisualStudio/feedback/details/1144980
(converted to C)
*/
FILE * __cdecl __iob_func(void)
{
 unsigned char * retaddr = (unsigned char*)_ReturnAddress();
#ifndef _M_AMD64

 if ( retaddr[0] != 0x83 || retaddr[1] != 0xC0 )
    return stdin;
 switch ( retaddr[2] )
 {
    case 0x20: return (FILE*)((char*)stdout - 0x20);
    case 0x40: return (FILE*)((char*)stderr - 0x40);
    default:return stdin;
 }
#else
 if ( retaddr[0] != 0x48 || retaddr[1] != 0x83 || retaddr[2] != 0xC0 )
    return stdin;
 switch ( retaddr[3] )
 {
    case 0x30: return (FILE*)((char*)stdout - 0x30);
    case 0x60: return (FILE*)((char*)stderr - 0x60);
    default:return stdin;
 }
#endif
}

#endif
#endif
#endif
