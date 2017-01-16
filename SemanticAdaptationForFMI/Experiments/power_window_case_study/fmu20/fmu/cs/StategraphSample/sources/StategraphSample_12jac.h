/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define StategraphSample_INDEX_JAC_D 3
  int StategraphSample_functionJacD_column(void* data, threadData_t *threadData);
  int StategraphSample_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */
#define $PuSeedD data->simulationInfo->analyticJacobians[3].seedVars[0]

#if defined(__cplusplus)
extern "C" {
#endif
  #define StategraphSample_INDEX_JAC_C 2
  int StategraphSample_functionJacC_column(void* data, threadData_t *threadData);
  int StategraphSample_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */

#if defined(__cplusplus)
extern "C" {
#endif
  #define StategraphSample_INDEX_JAC_B 1
  int StategraphSample_functionJacB_column(void* data, threadData_t *threadData);
  int StategraphSample_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */

#if defined(__cplusplus)
extern "C" {
#endif
  #define StategraphSample_INDEX_JAC_A 0
  int StategraphSample_functionJacA_column(void* data, threadData_t *threadData);
  int StategraphSample_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */


