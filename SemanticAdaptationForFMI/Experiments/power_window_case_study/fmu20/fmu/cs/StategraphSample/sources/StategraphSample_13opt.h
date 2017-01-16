#if defined(__cplusplus)
  extern "C" {
#endif
  int StategraphSample_mayer(DATA* data, modelica_real** res, short*);
  int StategraphSample_lagrange(DATA* data, modelica_real** res, short *, short *);
  int StategraphSample_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int StategraphSample_setInputData(DATA *data, const modelica_boolean file);
  int StategraphSample_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif