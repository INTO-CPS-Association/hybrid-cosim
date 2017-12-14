	/*==========================================================================*/ 
	/*  Description: Refrigerant property subroutines from IPM 5.0
	/*  Author: Weijiang Zhang (weijiang.zhang@carrier.utc.com)
	/*  Copyright reserved by Carrier M&A KCG, 2007
	/*  Date: 2007.7.12 
	/*==========================================================================*/
	#include "math.h"
	// extern all function list
	extern  double FT_PX(const double dP,const double dX);
	extern  double FTs_PX(const double dP,const double dX);
	extern  double FSH_PX(const double dP,const double dX);
	extern  double FH_PX(const double dP,const double dX);
	extern  double FRho_PX(const double dP,const double dX);
	extern  double FS_PX(const double dP,const double dX);
	extern  double FCp_PX(const double dP,const double dX);
	extern  double FLambda_PX(const double dP,const double dX);
	extern  double FMu_PX(const double dP,const double dX);
	extern  double FCpCv_PX(const double dP,const double dX);
	extern  double FIsotropic_PX(const double dP,const double dX);
	extern  double FA_PX(const double dP,const double dX);
	extern  double FTg_P(const double dP);
	extern  double FX_PH(const double dP,const double dH);
	extern  double FT_PH(const double dP,const double dH);
	extern  double FTs_PH(const double dP,const double dH);
	extern  double FSH_PH(const double dP,const double dH);
	extern  double FRho_PH(const double dP,const double dH);
	extern  double FS_PH(const double dP,const double dH);
	extern  double FCp_PH(const double dP,const double dH);
	extern  double FLambda_PH(const double dP,const double dH);
	extern  double FMu_PH(const double dP,const double dH);
	extern  double FCpCv_PH(const double dP,const double dH);
	extern  double FIsotropic_PH(const double dP,const double dH);
	extern  double FA_PH(const double dP,const double dH);
	extern  double FDRhoDP_PH(const double dP,const double dH);
	extern  double FDRhoDH_PH(const double dP,const double dH);
	extern  double FHls_PX(const double dP,const double dX);
	extern  double FHvs_PX(const double dP,const double dX);
	extern  double FRhols_PX(const double dP,const double dX);
	extern  double FRhovs_PX(const double dP,const double dX);
	extern  double FSls_PX(const double dP,const double dX);
	extern  double FSvs_PX(const double dP,const double dX);
	extern  double FCpls_PX(const double dP,const double dX);
	extern  double FCpvs_PX(const double dP,const double dX);
	extern  double FMuls_PX(const double dP,const double dX);
	extern  double FMuvs_PX(const double dP,const double dX);
	extern  double FLambdals_PX(const double dP,const double dX);
	extern  double FLambdavs_PX(const double dP,const double dX);
	extern  double FSurfTens_PX(const double dP,const double dX);
	extern  double FPs_TX(const double dT,const double dX); 
	extern  double FH_PT(const double dP,const double dT);
	extern  double FH_PS(const double dP,const double dS);
	extern  double FPc();
	// supporting functions
	extern  char* ShowLibInfo();
	extern  char* ShowSourceDataInfo();
	extern double FPercentPseudo();