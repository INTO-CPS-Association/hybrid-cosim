/* Algebraic */
#include "StategraphSample_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void StategraphSample_eqFunction_40(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_41(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_43(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_44(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_45(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_46(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_47(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_48(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_49(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_50(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_52(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_53(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_54(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_55(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_56(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_57(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_58(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_60(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  StategraphSample_eqFunction_40(data, threadData);

  StategraphSample_eqFunction_41(data, threadData);

  StategraphSample_eqFunction_43(data, threadData);

  StategraphSample_eqFunction_44(data, threadData);

  StategraphSample_eqFunction_45(data, threadData);

  StategraphSample_eqFunction_46(data, threadData);

  StategraphSample_eqFunction_47(data, threadData);

  StategraphSample_eqFunction_48(data, threadData);

  StategraphSample_eqFunction_49(data, threadData);

  StategraphSample_eqFunction_50(data, threadData);

  StategraphSample_eqFunction_52(data, threadData);

  StategraphSample_eqFunction_53(data, threadData);

  StategraphSample_eqFunction_54(data, threadData);

  StategraphSample_eqFunction_55(data, threadData);

  StategraphSample_eqFunction_56(data, threadData);

  StategraphSample_eqFunction_57(data, threadData);

  StategraphSample_eqFunction_58(data, threadData);

  StategraphSample_eqFunction_60(data, threadData);
}
/* for continuous time variables */
int StategraphSample_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  StategraphSample_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
