/* Algebraic */
#include "PW_PowerSystem_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void PW_PowerSystem_eqFunction_122(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_137(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_144(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_146(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_147(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_149(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_150(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_151(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_152(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_153(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_154(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_155(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_167(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_168(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_169(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_170(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_175(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_176(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_177(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_188(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_189(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_190(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_191(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_192(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_193(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_194(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_195(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_121(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_198(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_197(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_196(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  PW_PowerSystem_eqFunction_122(data, threadData);

  PW_PowerSystem_eqFunction_137(data, threadData);

  PW_PowerSystem_eqFunction_144(data, threadData);

  PW_PowerSystem_eqFunction_146(data, threadData);

  PW_PowerSystem_eqFunction_147(data, threadData);

  PW_PowerSystem_eqFunction_149(data, threadData);

  PW_PowerSystem_eqFunction_150(data, threadData);

  PW_PowerSystem_eqFunction_151(data, threadData);

  PW_PowerSystem_eqFunction_152(data, threadData);

  PW_PowerSystem_eqFunction_153(data, threadData);

  PW_PowerSystem_eqFunction_154(data, threadData);

  PW_PowerSystem_eqFunction_155(data, threadData);

  PW_PowerSystem_eqFunction_167(data, threadData);

  PW_PowerSystem_eqFunction_168(data, threadData);

  PW_PowerSystem_eqFunction_169(data, threadData);

  PW_PowerSystem_eqFunction_170(data, threadData);

  PW_PowerSystem_eqFunction_175(data, threadData);

  PW_PowerSystem_eqFunction_176(data, threadData);

  PW_PowerSystem_eqFunction_177(data, threadData);

  PW_PowerSystem_eqFunction_188(data, threadData);

  PW_PowerSystem_eqFunction_189(data, threadData);

  PW_PowerSystem_eqFunction_190(data, threadData);

  PW_PowerSystem_eqFunction_191(data, threadData);

  PW_PowerSystem_eqFunction_192(data, threadData);

  PW_PowerSystem_eqFunction_193(data, threadData);

  PW_PowerSystem_eqFunction_194(data, threadData);

  PW_PowerSystem_eqFunction_195(data, threadData);

  PW_PowerSystem_eqFunction_121(data, threadData);

  PW_PowerSystem_eqFunction_198(data, threadData);

  PW_PowerSystem_eqFunction_197(data, threadData);

  PW_PowerSystem_eqFunction_196(data, threadData);
}
/* for continuous time variables */
int PW_PowerSystem_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  PW_PowerSystem_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
