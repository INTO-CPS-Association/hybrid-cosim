/*!
    \file
    
    \attention <b> Subject to the EAR </b>
    
    \attention
    <b> ECCN: EAR99. </b> This information is subject to the export control laws of the
    United States, specifically including the Export Administration Regulations (EAR), 15 C.F.R. Part 730
    et seq.  Transfer, retransfer or disclosure of this data by any means to a non-US person (individual
    or company), whether in the U.S. or abroad, without any required export license or other approval from
    the U.S. Govt. is prohibited.
    
    \attention
    <b> UTC Proprietary. </b> This material contains proprietary information of United Technologies Corporation.
    Any copying, distribution, or dissemination of the contents of this material is strictly prohibited and may be
    unlawful without the express written permission of UTC. If you have obtained this material in error, please
    notify the UTRC IP Counsel at (860) 610-7339 immediately.
*/
#ifndef GENERIC_REFRIGERANT_HPP
#define GENERIC_REFRIGERANT_HPP

//#include <sstream>
//return multiple properties
//#include "RefrigerantInterface.hpp"
//#include "RefrigerantEnum.h"
enum RefrigerantID
{
	  R1233zd,
      R410A,
      R134a,
      R1234ze,
      R22,
      R290,
      R744,
      R452A,
      R718,
      R404A,
    NUM_REFRIGERANTS
};

// convert variable var to string
//template <typename T>
//std::string lexical_cast(T var)
//{
//    std::ostringstream os;
//    os << var;
//    return os.str();
//}
/*
// enumeration of all refrigerant IDs
enum RefrigerantID
{
    R1233zd,
    R410A,
    R134a,
    R1234ze,
    R22,
    R290,
    R404A,
    R407C,
    R744,
	R452A,
	R718,
    NUM_REFRIGERANTS
};//please add refrigerant in the end and do not insert in the middle

static const std::string refName[] = {"R1233zd",
                                      "R410A",
                                      "R134a",
                                      "R1234ze",
                                      "R22",
                                      "R290",
                                      "R404A",
                                      "R407C",
                                      "R744",
									  "R452A",
									  "R718"
                                     };


*/



#ifdef __cplusplus
extern "C" {
#endif

struct GenRefPropertiesPipev2
    {
        double T;
        double Ts;
        double rho;  
        double Cp;
        double mu;
        double lambda;
    };

struct GenRefPropertiesPipeph
    {
        double T;
        double Ts;
        double rho;  
        double Cp;
        double mu;
        double lambda;
		double ddph;
		double ddhp;
    };

struct GenRefPropertiesPipepx
    {
        double T;
        double Ts;
        double rho;  
		double h;
		double Cp;
        double mu;
        double lambda;
        double dhpx;
        double dhxp;
		double dvpx;
        double dvxp;
}; 


    struct SatRefPropertiesPipe
    {
        double rhosl;     //liquid specific volume
        double rhosv;
        double hsl;
        double hsv;
        double Cpsl;
        double Cpsv;
        double musl;
        double musv;
        double lambdasl;
        double lambdasv;
        double sigma;
    };

 struct GenRefProperties
    {
        double T;
        double Ts;
        double v;      
        double h;
        double s;
        double Cp;
        double mu;
        double lambda;
        double CpCv;
        double n_is;    //isentropic exponent
        double c;       //sonic velocity
        double dTglide; //temperature gliding
    };

    struct SatRefProperties
    {
        double vsl;     //liquid specific volume
        double vsv;
        double hsl;
        double hsv;
        double ssl;
        double ssv;
        double Cpsl;
        double Cpsv;
        double musl;
        double musv;
        double lambdasl;
        double lambdasv;
        double sigma;
		double csl;
		double csv;
    };
	 struct GenRefPropertiesAll
    {
		double p;
		double x;
        double T;
        double Ts;
        double v;      
        double h;
        double s;
        double Cp;
        double mu;
        double lambda;
        double CpCv;
        double n_is;    //isentropic exponent
        double c;       //sonic velocity
        double dTglide; //temperature gliding
    };
	struct pxProperties
    {
		double p;
		double x;
    };



void computeGenValuesPipePH_px(int ID, const double p, const double x,struct GenRefPropertiesPipeph* GenPropPipe,int errorFlag);
void computeGenValuesPipePX_px(int ID, const double p, const double x,struct GenRefPropertiesPipepx* GenPropPipe,int errorFlag);
void computeGenValuesPipev2_px(int ID, const double p, const double x,struct GenRefPropertiesPipev2* GenPropPipe,int errorFlag);
void computeSatValuesPipe_px(int ID, const double p, const double x, struct SatRefPropertiesPipe* SatPropPipe,int errorFlag);

void computeGenValues_px(int ID, const double p, const double x, struct GenRefProperties* GenProp,int errorFlag);
void computeGenValues2_px(int ID, const double p, const double x, struct GenRefProperties* GenProp, int errorFlag);
void computeSatValues_px(int ID, const double p, const double x, struct SatRefProperties* SatProp,int errorFlag);
void computeGenDxValues_px(int ID, const double p, const double x, struct GenRefProperties* GenDxProp,int errorFlag);
void computeSatDxValues_px(int ID, const double p, const double x, struct SatRefProperties* SatDxProp,int errorFlag);
void computeGenDpValues_px(int ID, const double p, const double x, struct GenRefProperties* GenDpProp,int errorFlag);
void computeSatDpValues_px(int ID, const double p, const double x, struct SatRefProperties* SatDpProp,int errorFlag);
void computeGenThermalValues_px(int ID, double p, double x, struct GenThermalPro* GenThermal, int errorFlag);  //added 12-15
void computeGenTransportValues_px(int ID, double p, double x, struct GenTransportPro* GenTransport, int errorFlag);  //added 12-15
void computeSatThermalValues_px(int ID, double p, double x, struct SatThermalPro* SatThermal, int errorFlag);  //added 12-15
void computeSatTransportValues_px(int ID, double p, double x, struct SatTransportPro* SatTransport, int errorFlag); //added 12-15
void computeConcentration_px(int ID, double p, double x, struct Concentration * concentration);  //added 12-15
///////////////////////////
void computeGenValues_ph(int ID, const double p, const double h, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_ph(int ID, const double p, const double h, struct SatRefProperties* SatProp,int errorFlag);
double x_pT       (int ID, const double p, const double T);
void computeGenValues_pT(int ID, const double p, const double T, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_pT(int ID, const double p, const double T, struct SatRefProperties* SatProp,int errorFlag);

void px_TTs       (int ID,const double T, const double Ts, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_TTs(int ID, const double T, const double Ts, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_TTs(int ID, const double T, const double Ts, struct SatRefProperties* SatProp,int errorFlag);

void px_Th       (int ID,const double T, const double h, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_Th(int ID, const double T, const double h, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_Th(int ID, const double T, const double h, struct SatRefProperties* SatProp,int errorFlag);

void computeGenValues_Tx(int ID, const double T, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_Tx(int ID, const double T, const double x, struct SatRefProperties* SatProp,int errorFlag);

double p_Tsx       (int ID, const double Ts, const double x);
void computeGenValues_Tsx(int ID, const double Ts, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_Tsx(int ID, const double Ts, const double x, struct SatRefProperties* SatProp,int errorFlag);

double p_hx       (int ID, const double h, const double x);
void computeGenValues_hx(int ID, const double h, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_hx(int ID, const double h, const double x, struct SatRefProperties* SatProp,int errorFlag);


double p_vx       (int ID, const double v, const double x);
void computeGenValues_vx(int ID, const double v, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_vx(int ID, const double v, const double x, struct SatRefProperties* SatProp,int errorFlag);

double p_dTshx      (int ID, const double dTsh, const double x);
void computeGenValues_dTshx(int ID, const double dTsh, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_dTshx(int ID, const double dTsh, const double x, struct SatRefProperties* SatProp,int errorFlag);

double p_sx      (int ID, const double s, const double x);
void computeGenValues_sx(int ID, const double s, const double x, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_sx(int ID, const double s, const double x, struct SatRefProperties* SatProp,int errorFlag);

void px_TdTsh       (int ID,const double T, const double dTsh, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_TdTsh(int ID, const double T, const double dTsh, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_TdTsh(int ID, const double T, const double dTsh, struct SatRefProperties* SatProp,int errorFlag);

void px_Ts       (int ID,const double T, const double s, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_Ts(int ID, const double T, const double s, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_Ts(int ID, const double T, const double s, struct SatRefProperties* SatProp,int errorFlag);



void px_hs       (int ID,const double h, const double s, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_hs(int ID, const double h, const double s, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_hs(int ID, const double h, const double s, struct SatRefProperties* SatProp,int errorFlag);

void px_hdTsh       (int ID,const double h, const double dTsh, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_hdTsh(int ID, const double h, const double dTsh, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_hdTsh(int ID, const double h, const double dTsh, struct SatRefProperties* SatProp,int errorFlag);

void px_sdTsh       (int ID,const double s, const double dTsh, struct pxProperties* pxProp,int errorFlag);
void computeGenValues_sdTsh(int ID, const double s, const double dTsh, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_sdTsh(int ID, const double s, const double dTsh, struct SatRefProperties* SatProp,int errorFlag);

/* input T & v     */
void px_Tv(int ID, double T, double v, struct pxProperties* pxProp, int errorFlag);
void computeGenValues_Tv(int ID, const double T, const double v, struct GenRefPropertiesAll* GenProp,int errorFlag);
void computeSatValues_Tv(int ID, const double T, const double v, struct SatRefProperties* SatProp,int errorFlag);

/*  input p & v   */
double x_pv (int ID, const double p, const double v, int errorFlag);
void computeGenValues_pv(int ID, const double p, const double v, struct GenRefPropertiesAll* GenProp, int errorFlag);  //added 1-7-2016
void computeSatValues_pv(int ID, const double p, const double v, struct SatRefProperties* SatProp, int errorFlag);  //added 1-7-2016

/*  input p & dTsh   */
double x_pdTsh (int ID, const double p, const double dTsh, int errorFlag);
void computeGenValues_pdTsh(int ID, const double p, const double dTsh, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_pdTsh(int ID, const double p, const double dTsh, struct SatRefProperties* SatProp, int errorFlag);

/*  input p & s   */
double x_ps (int ID, double p, double s, int errorFlag);
void computeGenValues_ps(int ID, double p, double s,  struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_ps(int ID, double p, double s,  struct SatRefProperties* SatProp, int errorFlag);


/* intput Ts & h */
void px_Tsh(int ID, const double Ts, const double h, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_Tsh(int ID,  const double Ts, const double h, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_Tsh(int ID, const double Ts, const double h, struct SatRefProperties* SatProp, int errorFlag);

/* intput Ts & v */
void px_Tsv(int ID, const double Ts, const double v, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_Tsv(int ID,  const double Ts, const double v, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_Tsv(int ID, const double Ts, const double v, struct SatRefProperties* SatProp, int errorFlag);

/* intput Ts & dTsh */
void computeGenValues_TsdTsh(int ID,  const double Ts, const double dTsh, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_TsdTsh(int ID, const double Ts, const double dTsh, struct SatRefProperties* SatProp, int errorFlag);

/*        input Ts and s               */
void px_Tss(int ID, double Ts, double s, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_Tss(int ID,  double Ts, double s, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_Tss(int ID, double Ts, double s, struct SatRefProperties* SatProp, int errorFlag);

/*        input v and dTsh               */
void px_vdTsh(int ID, double v, double dTsh, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_vdTsh(int ID,  double v, double dTsh, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_vdTsh(int ID, double v, double dTsh, struct SatRefProperties* SatProp, int errorFlag);

/*        input v and s               */
void px_vs(int ID, double v, double s, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_vs(int ID,  double v, double s, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_vs(int ID, double v, double s, struct SatRefProperties* SatProp, int errorFlag);

/*        input h and v               */
void px_hv(int ID, double h, double v, struct pxProperties *pxProp, int errorFlag);
void computeGenValues_hv(int ID,  double h, double v, struct GenRefPropertiesAll* GenProp, int errorFlag);
void computeSatValues_hv(int ID, double h, double v, struct SatRefProperties* SatProp, int errorFlag);


double T_px        (int ID, const double p, const double x);
double Ts_px       (int ID, const double p, const double x);
double dTsh_px     (int ID, const double p, const double x);
double h_px        (int ID, const double p, const double x);
double rho_px      (int ID, const double p, const double x);
double v_px      (int ID, const double p, const double x);
double s_px        (int ID, const double p, const double x);
double Cp_px       (int ID, const double p, const double x);




double dTdx_px         (int ID, const double p, const double x);
double dTdp_px         (int ID, const double p, const double x);
double dTsdx_px         (int ID, const double p, const double x);
double dTsdp_px         (int ID, const double p, const double x);
double dCpdx_px        (int ID, const double p, const double x);
double dCpdp_px        (int ID, const double p, const double x);
double drhodx2_px      (int ID, const double p, const double x);
double drhodp2_px      (int ID, const double p, const double x);
double dhdx_px        (int ID, const double p, const double x);
double dhdp_px        (int ID, const double p, const double x);
double dsdx_px        (int ID, const double p, const double x);
double dsdp_px        (int ID, const double p, const double x);
double dmudx_px        (int ID, const double p, const double x);
double dmudp_px        (int ID, const double p, const double x);
double dlambdadx_px    (int ID, const double p, const double x);
double dlambdadp_px      (int ID, const double p, const double x);
double dCpCvdx_px        (int ID, const double p, const double x);
double dCpCvdp_px        (int ID, const double p, const double x);
double dn_isdx_px        (int ID, const double p, const double x);
double dn_isdp_px        (int ID, const double p, const double x);
double dcdx_px        (int ID, const double p, const double x);
double dcdp_px        (int ID, const double p, const double x);
double ddTglidedx_px        (int ID, const double p, const double x);
double ddTglidedp_px        (int ID, const double p, const double x);

double dsigmadx_px        (int ID, const double p, const double x);
double dsigmadp_px        (int ID, const double p, const double x);
double drhosldx_px        (int ID, const double p, const double x);
double drhosldp_px        (int ID, const double p, const double x);
double drhosvdx_px        (int ID, const double p, const double x);
double drhosvdp_px        (int ID, const double p, const double x);
double dhsldx_px        (int ID, const double p, const double x);
double dhsldp_px        (int ID, const double p, const double x);
double dhsvdx_px        (int ID, const double p, const double x);
double dhsvdp_px        (int ID, const double p, const double x);
double dssldx_px        (int ID, const double p, const double x);
double dssldp_px        (int ID, const double p, const double x);
double dssvdx_px        (int ID, const double p, const double x);
double dssvdp_px        (int ID, const double p, const double x);
double dCpsldx_px        (int ID, const double p, const double x);
double dCpsldp_px        (int ID, const double p, const double x);
double dCpsvdx_px        (int ID, const double p, const double x);
double dCpsvdp_px        (int ID, const double p, const double x);
double dmusldx_px        (int ID, const double p, const double x);
double dmusldp_px        (int ID, const double p, const double x);
double dmusvdx_px        (int ID, const double p, const double x);
double dmusvdp_px        (int ID, const double p, const double x);
double dlambdasldx_px        (int ID, const double p, const double x);
double dlambdasldp_px        (int ID, const double p, const double x);
double dlambdasvdx_px        (int ID, const double p, const double x);
double dlambdasvdp_px        (int ID, const double p, const double x);
double dcsldx_px     (int ID, const double p, const double x);
double dcsldp_px     (int ID, const double p, const double x);
double dcsvdp_px    (int ID, const double p, const double x);
double dcsvdx_px    (int ID, const double p, const double x);



double lambda_px   (int ID, const double p, const double x);
double mu_px       (int ID, const double p, const double x);
double nu_px       (int ID, const double p, const double x);
double Pr_px       (int ID, const double p, const double x);
double CpCv_px     (int ID, const double p, const double x);
double n_is_px     (int ID, const double p, const double x);
double c_px        (int ID, const double p, const double x);
double dTglide_p   (int ID, const double p);

double x_ph        (int ID, const double p, const double h);
double T_ph        (int ID, const double p, const double h);
double Ts_ph       (int ID, const double p, const double h);
double dTsh_ph     (int ID, const double p, const double h);
double rho_ph      (int ID, const double p, const double h);
double s_ph        (int ID, const double p, const double h);
double Cp_ph       (int ID, const double p, const double h);
double lambda_ph   (int ID, const double p, const double h);
double mu_ph       (int ID, const double p, const double h);
double nu_ph       (int ID, const double p, const double h);
double Pr_ph       (int ID, const double p, const double h);
double CpCv_ph     (int ID, const double p, const double h);
double n_is_ph     (int ID, const double p, const double h);
double c_ph        (int ID, const double p, const double h);
double drhodp_ph   (int ID, const double p, const double h);
double drhodh_ph   (int ID, const double p, const double h);

double hsl_px      (int ID, const double p, const double x);
double hsv_px      (int ID, const double p, const double x);
double rhosl_px    (int ID, const double p, const double x);
double rhosv_px    (int ID, const double p, const double x);
double ssl_px      (int ID, const double p, const double x);
double ssv_px      (int ID, const double p, const double x);
double Cpsl_px     (int ID, const double p, const double x);
double Cpsv_px     (int ID, const double p, const double x);
double musl_px     (int ID, const double p, const double x);
double musv_px     (int ID, const double p, const double x);
double lambdasl_px (int ID, const double p, const double x);
double lambdasv_px (int ID, const double p, const double x);
double csl_px         (int ID, const double p, const double x);
double csv_px        (int ID, const double p, const double x);
double sigma_px    (int ID, const double p, const double x);

double p_Tx       (int ID, const double T, const double x);
double h_pT        (int ID, const double p, const double T);
double h_ps        (int ID, const double p, const double s);
double pc          (int ID);
double pcPseudo    (int ID);
double pchlPseudo  (int ID);
double pchvPseudo  (int ID);
double Tc          (int ID);
double xilMax  (int ID);
double MolarMass (int ID);

//Input files
double qbegin (int ID);
double qend (int ID);
double pbegin (int ID);
double pend (int ID);
double qinc (int ID);
double deltap (int ID);
double Tlow (int ID);
double Thigh (int ID);
double Tbeg (int ID);
double Tend (int ID);
double Tinc (int ID);


// supporting functions
char* getName          (int ID);
const char* getVersion (int ID);
double FPercentPseudo  (int ID);
void getRefComposition( int ID, const char* refCon[]); //added 12-15
int getRefComNum(int ID);

double vx_px (int ID, const double p, const double x);
double vp_px (int ID, const double p, const double x);
double hp_px (int ID, const double p, const double x);
double hx_px (int ID, const double p, const double x);


//
//double F_to_K(const double& T);

/// \todo SK: Are these functions not used, why is ID not passed as a parameter?
double drhodp_px(int ID, const double p, const double x);
double drhodh_px(int ID, const double p, const double x);

#ifdef __cplusplus
} // extern C
#endif

#endif // GENERIC_REFRIGERANT_HPP

