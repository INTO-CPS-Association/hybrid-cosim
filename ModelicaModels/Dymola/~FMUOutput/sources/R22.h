	/*==========================================================================*/ 
	/*  Description: Refrigerant property subroutines from IPM 5.0
	/*  Author: Weijiang Zhang (weijiang.zhang@carrier.utc.com)
	/*  Copyright reserved by Carrier M&A KCG, 2007
	/*  Date: 2007.7.12 
	/*==========================================================================*/
	#include "math.h"
	// extern  all function list
	extern   double FT_PX_R22(const double dP,const double dX);
	extern   double FTs_PX_R22(const double dP,const double dX);
	extern   double FSH_PX_R22(const double dP,const double dX);
	extern   double FH_PX_R22(const double dP,const double dX);
	extern   double FRho_PX_R22(const double dP,const double dX);
	extern   double FS_PX_R22(const double dP,const double dX);
	extern   double FCp_PX_R22(const double dP,const double dX);
	extern   double FLambda_PX_R22(const double dP,const double dX);
	extern   double FMu_PX_R22(const double dP,const double dX);
	extern   double FCpCv_PX_R22(const double dP,const double dX);
	extern   double FIsotropic_PX_R22(const double dP,const double dX);
	extern   double FA_PX_R22(const double dP,const double dX);
	extern   double FTg_P_R22(const double dP);
	extern   double FX_PH_R22(const double dP,const double dH);
	extern   double FT_PH_R22(const double dP,const double dH);
	extern   double FTs_PH_R22(const double dP,const double dH);
	extern   double FSH_PH_R22(const double dP,const double dH);
	extern   double FRho_PH_R22(const double dP,const double dH);
	extern   double FS_PH_R22(const double dP,const double dH);
	extern   double FCp_PH_R22(const double dP,const double dH);
	extern   double FLambda_PH_R22(const double dP,const double dH);
	extern   double FMu_PH_R22(const double dP,const double dH);
	extern   double FCpCv_PH_R22(const double dP,const double dH);
	extern   double FIsotropic_PH_R22(const double dP,const double dH);
	extern   double FA_PH_R22(const double dP,const double dH);
	extern   double FDRhoDP_PH_R22(const double dP,const double dH);
	extern   double FDRhoDH_PH_R22(const double dP,const double dH);
	extern   double FHls_PX_R22(const double dP,const double dX);
	extern   double FHvs_PX_R22(const double dP,const double dX);
	extern   double FRhols_PX_R22(const double dP,const double dX);
	extern   double FRhovs_PX_R22(const double dP,const double dX);
	extern   double FSls_PX_R22(const double dP,const double dX);
	extern   double FSvs_PX_R22(const double dP,const double dX);
	extern   double FCpls_PX_R22(const double dP,const double dX);
	extern   double FCpvs_PX_R22(const double dP,const double dX);
	extern   double FMuls_PX_R22(const double dP,const double dX);
	extern   double FMuvs_PX_R22(const double dP,const double dX);
	extern   double FLambdals_PX_R22(const double dP,const double dX);
	extern   double FLambdavs_PX_R22(const double dP,const double dX);
	extern   double FSurfTens_PX_R22(const double dP,const double dX);
	extern   double FPs_TX_R22(const double dT,const double dX); 
	extern   double FH_PT_R22(const double dP,const double dT);
	extern   double FH_PS_R22(const double dP,const double dS);
	extern   double FPc_R22();
	// supporting functions
	extern   char* ShowLibInfo_R22();
	extern   char* ShowSourceDataInfo_R22();
	extern   double FPercentPseudo_R22();

	//double FGenIndex_PH(const int CI, const double P,const double H);

	extern   double FDDPH_PX_R22(const double dP,const double dX);
	extern   double FDDHP_PX_R22(const double dP,const double dX);