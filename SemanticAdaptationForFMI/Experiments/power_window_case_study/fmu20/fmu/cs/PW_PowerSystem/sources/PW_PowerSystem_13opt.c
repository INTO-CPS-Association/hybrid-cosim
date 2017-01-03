/* Optimization */
#include "PW_PowerSystem_model.h"
#include "PW_PowerSystem_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif
int PW_PowerSystem_mayer(DATA* data, modelica_real** res,short *i){return -1;}
int PW_PowerSystem_lagrange(DATA* data, modelica_real** res, short * i1, short*i2){return -1;}
int PW_PowerSystem_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt){return -1;}
int PW_PowerSystem_setInputData(DATA *data, const modelica_boolean file){return -1;}
int PW_PowerSystem_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t){return -1;}
#if defined(__cplusplus)
}
#endif