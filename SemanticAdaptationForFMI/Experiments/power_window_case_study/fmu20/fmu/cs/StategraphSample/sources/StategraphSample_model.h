/* Simulation code for StategraphSample generated by the OpenModelica Compiler v1.12.0-dev-77-g56dc448 (32-bit). */
#if !defined(StategraphSample__MODEL_H)
#define StategraphSample__MODEL_H
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "simulation/simulation_info_json.h"
#include "simulation/simulation_runtime.h"
#include "util/omc_error.h"
#include "simulation/solver/model_help.h"
#include "simulation/solver/delay.h"
#include "simulation/solver/linearSystem.h"
#include "simulation/solver/nonlinearSystem.h"
#include "simulation/solver/mixedSystem.h"

#include <string.h>

#include "StategraphSample_functions.h"

#define Modelica_StateGraph_Temporary_anyTrue_index 0

extern void StategraphSample_callExternalObjectConstructors(DATA *data, threadData_t *threadData);
extern void StategraphSample_callExternalObjectDestructors(DATA *_data, threadData_t *threadData);
#if !defined(OMC_NUM_NONLINEAR_SYSTEMS) || OMC_NUM_NONLINEAR_SYSTEMS>0
#endif
#if !defined(OMC_NUM_LINEAR_SYSTEMS) || OMC_NUM_LINEAR_SYSTEMS>0
#endif
#if !defined(OMC_NUM_MIXED_SYSTEMS) || OMC_NUM_MIXED_SYSTEMS>0
#endif
#if !defined(OMC_NO_STATESELECTION)
extern void StategraphSample_initializeStateSets(int nStateSets, STATE_SET_DATA* statesetData, DATA *data);
#endif
extern int StategraphSample_functionAlgebraics(DATA *data, threadData_t *threadData);
extern int StategraphSample_function_storeDelayed(DATA *data, threadData_t *threadData);
extern int StategraphSample_updateBoundVariableAttributes(DATA *data, threadData_t *threadData);
extern int StategraphSample_functionInitialEquations(DATA *data, threadData_t *threadData);
extern int StategraphSample_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData);
extern int StategraphSample_functionRemovedInitialEquations(DATA *data, threadData_t *threadData);
extern int StategraphSample_updateBoundParameters(DATA *data, threadData_t *threadData);
extern int StategraphSample_checkForAsserts(DATA *data, threadData_t *threadData);
extern int StategraphSample_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData);
extern int StategraphSample_function_ZeroCrossings(DATA *data, threadData_t *threadData, double* gout);
extern int StategraphSample_function_updateRelations(DATA *data, threadData_t *threadData, int evalZeroCross);
extern int StategraphSample_checkForDiscreteChanges(DATA *data, threadData_t *threadData);
extern const char* StategraphSample_zeroCrossingDescription(int i, int **out_EquationIndexes);
extern const char* StategraphSample_relationDescription(int i);
extern void StategraphSample_function_initSample(DATA *data, threadData_t *threadData);
extern int StategraphSample_initialAnalyticJacobianG(void* data, threadData_t *threadData);
extern int StategraphSample_initialAnalyticJacobianA(void* data, threadData_t *threadData);
extern int StategraphSample_initialAnalyticJacobianB(void* data, threadData_t *threadData);
extern int StategraphSample_initialAnalyticJacobianC(void* data, threadData_t *threadData);
extern int StategraphSample_initialAnalyticJacobianD(void* data, threadData_t *threadData);
extern int StategraphSample_functionJacG_column(void* data, threadData_t *threadData);
extern int StategraphSample_functionJacA_column(void* data, threadData_t *threadData);
extern int StategraphSample_functionJacB_column(void* data, threadData_t *threadData);
extern int StategraphSample_functionJacC_column(void* data, threadData_t *threadData);
extern int StategraphSample_functionJacD_column(void* data, threadData_t *threadData);
extern const char* StategraphSample_linear_model_frame(void);
extern const char* StategraphSample_linear_model_datarecovery_frame(void);
extern int StategraphSample_mayer(DATA* data, modelica_real** res, short *);
extern int StategraphSample_lagrange(DATA* data, modelica_real** res, short *, short *);
extern int StategraphSample_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
extern int StategraphSample_setInputData(DATA *data, const modelica_boolean file);
extern int StategraphSample_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
extern void StategraphSample_function_initSynchronous(DATA * data, threadData_t *threadData);
extern void StategraphSample_function_updateSynchronous(DATA * data, threadData_t *threadData, long i);
extern int StategraphSample_function_equationsSynchronous(DATA * data, threadData_t *threadData, long i);
extern void StategraphSample_read_input_fmu(MODEL_DATA* modelData, SIMULATION_INFO* simulationData);
extern void StategraphSample_function_savePreSynchronous(DATA *data, threadData_t *threadData);
extern int StategraphSample_inputNames(DATA* data, char ** names);
extern int StategraphSample_initializeDAEmodeData(DATA *data, DAEMODE_DATA*);
extern int StategraphSample_functionLocalKnownVars(DATA*, threadData_t*);

#include "StategraphSample_literals.h"




#if defined(HPCOM) && !defined(_OPENMP)
  #error "HPCOM requires OpenMP or the results are wrong"
#endif
#if defined(_OPENMP)
  #include <omp.h>
#else
  /* dummy omp defines */
  #define omp_get_max_threads() 1
#endif

#endif

