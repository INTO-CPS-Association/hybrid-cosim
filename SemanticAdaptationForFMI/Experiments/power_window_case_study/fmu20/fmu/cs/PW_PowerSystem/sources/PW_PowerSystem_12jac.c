/* Jacobians */
#include "PW_PowerSystem_model.h"
#include "PW_PowerSystem_12jac.h"

int PW_PowerSystem_initialAnalyticJacobianLSJac53(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac53;
  const int colPtrIndex[1+1] = {0,1};
  const int rowIndex[1] = {0};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 1;
  data->simulationInfo->analyticJacobians[index].sizeRows = 1;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 3;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(3,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((1+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(1*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(1*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 1;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (1+1)*sizeof(int));
  
  for(i=2;i<1+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 1*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 1;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianLSJac52(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac52;
  const int colPtrIndex[1+2] = {0,2,2};
  const int rowIndex[4] = {0,1,0,1};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 2;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 5;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(5,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((2+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 4;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(2*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 2;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (2+1)*sizeof(int));
  
  for(i=2;i<2+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 4*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 2;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianLSJac51(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac51;
  const int colPtrIndex[1+2] = {0,2,2};
  const int rowIndex[4] = {0,1,0,1};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 2;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 5;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(5,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((2+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 4;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(2*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 2;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (2+1)*sizeof(int));
  
  for(i=2;i<2+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 4*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 2;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianLSJac50(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac50;
  const int colPtrIndex[1+1] = {0,1};
  const int rowIndex[1] = {0};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 1;
  data->simulationInfo->analyticJacobians[index].sizeRows = 1;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 3;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(3,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((1+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(1*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(1*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 1;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (1+1)*sizeof(int));
  
  for(i=2;i<1+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 1*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 1;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianLSJac49(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac49;
  const int colPtrIndex[1+2] = {0,2,2};
  const int rowIndex[4] = {0,1,0,1};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 2;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 5;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(5,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((2+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 4;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(2*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 2;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (2+1)*sizeof(int));
  
  for(i=2;i<2+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 4*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 2;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianLSJac48(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac48;
  const int colPtrIndex[1+2] = {0,2,2};
  const int rowIndex[4] = {0,1,0,1};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 2;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 5;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(5,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((2+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 4;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(2*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 2;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (2+1)*sizeof(int));
  
  for(i=2;i<2+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 4*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 2;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianD(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_D;
  const int colPtrIndex[1+3] = {0,0,0,0};
  const int rowIndex[0] = {};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 3;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 0;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(3,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(0,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((3+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(0*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 0;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(3*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 1;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (3+1)*sizeof(int));
  
  for(i=2;i<3+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 0*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[2] = 1;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianC(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_C;
  const int colPtrIndex[1+4] = {0,0,1,1,0};
  const int rowIndex[2] = {1,0};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 4;
  data->simulationInfo->analyticJacobians[index].sizeRows = 2;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 0;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(0,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((4+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(2*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 2;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 1;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (4+1)*sizeof(int));
  
  for(i=2;i<4+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 2*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[3] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[2] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 1;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianB(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_B;
  const int colPtrIndex[1+3] = {0,1,1,1};
  const int rowIndex[3] = {2,1,2};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 3;
  data->simulationInfo->analyticJacobians[index].sizeRows = 4;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 0;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(3,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(0,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((3+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(3*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 3;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(3*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 2;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (3+1)*sizeof(int));
  
  for(i=2;i<3+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 3*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[2] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 2;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 2;
  TRACE_POP
  return 0;
}

int PW_PowerSystem_initialAnalyticJacobianA(void* inData, threadData_t *threadData)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_A;
  const int colPtrIndex[1+4] = {0,3,3,2,0};
  const int rowIndex[8] = {0,1,2,1,2,3,1,2};
  int i = 0;
  
  data->simulationInfo->analyticJacobians[index].sizeCols = 4;
  data->simulationInfo->analyticJacobians[index].sizeRows = 4;
  data->simulationInfo->analyticJacobians[index].sizeTmpVars = 0;
  data->simulationInfo->analyticJacobians[index].seedVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].resultVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].tmpVars = (modelica_real*) calloc(0,sizeof(modelica_real));
  data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex = (unsigned int*) malloc((4+1)*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.index = (unsigned int*) malloc(8*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.numberOfNoneZeros = 8;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols = (unsigned int*) malloc(4*sizeof(int));
  data->simulationInfo->analyticJacobians[index].sparsePattern.maxColors = 3;
  data->simulationInfo->analyticJacobians[index].jacobian = NULL;
  
  /* write lead index of compressed sparse column */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex, colPtrIndex, (4+1)*sizeof(int));
  
  for(i=2;i<4+1;++i)
    data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i] += data->simulationInfo->analyticJacobians[index].sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(data->simulationInfo->analyticJacobians[index].sparsePattern.index, rowIndex, 8*sizeof(int));
  
  /* write color array */
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[0] = 1;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[2] = 2;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[3] = 3;
  data->simulationInfo->analyticJacobians[index].sparsePattern.colorCols[1] = 3;
  TRACE_POP
  return 0;
}


/*
 equation index: 184
 type: SIMPLE_ASSIGN
 der(motor._lesigma._i._$pDERLSJac53._dummyVarLSJac53) = 1.25 * motor_lesigma_vSeedLSJac53
 */
void PW_PowerSystem_eqFunction_184(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,184};
  $P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac53$PdummyVarLSJac53 = (1.25) * ($Pmotor_lesigma_vSeedLSJac53);
  TRACE_POP
}

/*
 equation index: 185
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac53._dummyVarLSJac53 = 3.2 * $DER.motor.lesigma.i.$pDERLSJac53.dummyVarLSJac53 + motor_lesigma_vSeedLSJac53
 */
void PW_PowerSystem_eqFunction_185(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,185};
  $P$res$P1$P$pDERLSJac53$PdummyVarLSJac53 = (3.2) * ($P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac53$PdummyVarLSJac53) + $Pmotor_lesigma_vSeedLSJac53;
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac53_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac53;
  PW_PowerSystem_eqFunction_184(data, threadData);

  PW_PowerSystem_eqFunction_185(data, threadData);
  
  TRACE_POP
  return 0;
}

/*
 equation index: 162
 type: SIMPLE_ASSIGN
 arm_sensor._p._v._$pDERLSJac52._dummyVarLSJac52 = idealCommutingSwitch1_s2SeedLSJac52 * (if greaterThreshold1.y then idealCommutingSwitch1.Ron else 1.0)
 */
void PW_PowerSystem_eqFunction_162(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,162};
  $Parm_sensor$Pp$Pv$P$pDERLSJac52$PdummyVarLSJac52 = ($PidealCommutingSwitch1_s2SeedLSJac52) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */:1.0));
  TRACE_POP
}

/*
 equation index: 163
 type: SIMPLE_ASSIGN
 $res._2._$pDERLSJac52._dummyVarLSJac52 = arm_sensor.p.v.$pDERLSJac52.dummyVarLSJac52 - idealCommutingSwitch1_s1SeedLSJac52 * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Ron)
 */
void PW_PowerSystem_eqFunction_163(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,163};
  $P$res$P2$P$pDERLSJac52$PdummyVarLSJac52 = $Parm_sensor$Pp$Pv$P$pDERLSJac52$PdummyVarLSJac52 - (($PidealCommutingSwitch1_s1SeedLSJac52) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */)));
  TRACE_POP
}

/*
 equation index: 164
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n2._i._$pDERLSJac52._dummyVarLSJac52 = (-idealCommutingSwitch1_s2SeedLSJac52) * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Goff)
 */
void PW_PowerSystem_eqFunction_164(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,164};
  $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac52$PdummyVarLSJac52 = ((-$PidealCommutingSwitch1_s2SeedLSJac52)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */));
  TRACE_POP
}

/*
 equation index: 165
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac52._dummyVarLSJac52 = idealCommutingSwitch1.n2.i.$pDERLSJac52.dummyVarLSJac52 - idealCommutingSwitch1_s1SeedLSJac52 * (if greaterThreshold1.y then idealCommutingSwitch1.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_165(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,165};
  $P$res$P1$P$pDERLSJac52$PdummyVarLSJac52 = $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac52$PdummyVarLSJac52 - (($PidealCommutingSwitch1_s1SeedLSJac52) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */:1.0)));
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac52_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac52;
  PW_PowerSystem_eqFunction_162(data, threadData);

  PW_PowerSystem_eqFunction_163(data, threadData);

  PW_PowerSystem_eqFunction_164(data, threadData);

  PW_PowerSystem_eqFunction_165(data, threadData);
  
  TRACE_POP
  return 0;
}

/*
 equation index: 131
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n1._i._$pDERLSJac51._dummyVarLSJac51 = (-idealCommutingSwitch2_s1SeedLSJac51) * (if convertToBoolean.y then idealCommutingSwitch2.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_131(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,131};
  $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac51$PdummyVarLSJac51 = ((-$PidealCommutingSwitch2_s1SeedLSJac51)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */:1.0));
  TRACE_POP
}

/*
 equation index: 132
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._p._v._$pDERLSJac51._dummyVarLSJac51 = idealCommutingSwitch2_s1SeedLSJac51 * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Ron)
 */
void PW_PowerSystem_eqFunction_132(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,132};
  $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac51$PdummyVarLSJac51 = ($PidealCommutingSwitch2_s1SeedLSJac51) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */));
  TRACE_POP
}

/*
 equation index: 133
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n2._i._$pDERLSJac51._dummyVarLSJac51 = (-idealCommutingSwitch2_s2SeedLSJac51) * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Goff)
 */
void PW_PowerSystem_eqFunction_133(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,133};
  $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac51$PdummyVarLSJac51 = ((-$PidealCommutingSwitch2_s2SeedLSJac51)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */));
  TRACE_POP
}

/*
 equation index: 134
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac51._dummyVarLSJac51 = idealCommutingSwitch2.n2.i.$pDERLSJac51.dummyVarLSJac51 + idealCommutingSwitch2.n1.i.$pDERLSJac51.dummyVarLSJac51
 */
void PW_PowerSystem_eqFunction_134(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,134};
  $P$res$P1$P$pDERLSJac51$PdummyVarLSJac51 = $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac51$PdummyVarLSJac51 + $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac51$PdummyVarLSJac51;
  TRACE_POP
}

/*
 equation index: 135
 type: SIMPLE_ASSIGN
 $res._2._$pDERLSJac51._dummyVarLSJac51 = idealCommutingSwitch2_s2SeedLSJac51 * (if convertToBoolean.y then idealCommutingSwitch2.Ron else 1.0) - idealCommutingSwitch2.p.v.$pDERLSJac51.dummyVarLSJac51
 */
void PW_PowerSystem_eqFunction_135(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,135};
  $P$res$P2$P$pDERLSJac51$PdummyVarLSJac51 = ($PidealCommutingSwitch2_s2SeedLSJac51) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */:1.0)) - $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac51$PdummyVarLSJac51;
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac51_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac51;
  PW_PowerSystem_eqFunction_131(data, threadData);

  PW_PowerSystem_eqFunction_132(data, threadData);

  PW_PowerSystem_eqFunction_133(data, threadData);

  PW_PowerSystem_eqFunction_134(data, threadData);

  PW_PowerSystem_eqFunction_135(data, threadData);
  
  TRACE_POP
  return 0;
}

/*
 equation index: 94
 type: SIMPLE_ASSIGN
 der(motor._lesigma._i._$pDERLSJac50._dummyVarLSJac50) = 0.3125 * motor_airGapDC_veiSeedLSJac50
 */
void PW_PowerSystem_eqFunction_94(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,94};
  $P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac50$PdummyVarLSJac50 = (0.3125) * ($Pmotor_airGapDC_veiSeedLSJac50);
  TRACE_POP
}

/*
 equation index: 95
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac50._dummyVarLSJac50 = 0.8 * $DER.motor.lesigma.i.$pDERLSJac50.dummyVarLSJac50 + motor_airGapDC_veiSeedLSJac50
 */
void PW_PowerSystem_eqFunction_95(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,95};
  $P$res$P1$P$pDERLSJac50$PdummyVarLSJac50 = (0.8) * ($P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac50$PdummyVarLSJac50) + $Pmotor_airGapDC_veiSeedLSJac50;
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac50_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac50;
  PW_PowerSystem_eqFunction_94(data, threadData);

  PW_PowerSystem_eqFunction_95(data, threadData);
  
  TRACE_POP
  return 0;
}

/*
 equation index: 72
 type: SIMPLE_ASSIGN
 arm_sensor._p._v._$pDERLSJac49._dummyVarLSJac49 = idealCommutingSwitch1_s2SeedLSJac49 * (if greaterThreshold1.y then idealCommutingSwitch1.Ron else 1.0)
 */
void PW_PowerSystem_eqFunction_72(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,72};
  $Parm_sensor$Pp$Pv$P$pDERLSJac49$PdummyVarLSJac49 = ($PidealCommutingSwitch1_s2SeedLSJac49) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */:1.0));
  TRACE_POP
}

/*
 equation index: 73
 type: SIMPLE_ASSIGN
 $res._2._$pDERLSJac49._dummyVarLSJac49 = arm_sensor.p.v.$pDERLSJac49.dummyVarLSJac49 - idealCommutingSwitch1_s1SeedLSJac49 * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Ron)
 */
void PW_PowerSystem_eqFunction_73(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,73};
  $P$res$P2$P$pDERLSJac49$PdummyVarLSJac49 = $Parm_sensor$Pp$Pv$P$pDERLSJac49$PdummyVarLSJac49 - (($PidealCommutingSwitch1_s1SeedLSJac49) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */)));
  TRACE_POP
}

/*
 equation index: 74
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n2._i._$pDERLSJac49._dummyVarLSJac49 = (-idealCommutingSwitch1_s2SeedLSJac49) * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Goff)
 */
void PW_PowerSystem_eqFunction_74(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,74};
  $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac49$PdummyVarLSJac49 = ((-$PidealCommutingSwitch1_s2SeedLSJac49)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */));
  TRACE_POP
}

/*
 equation index: 75
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac49._dummyVarLSJac49 = idealCommutingSwitch1.n2.i.$pDERLSJac49.dummyVarLSJac49 - idealCommutingSwitch1_s1SeedLSJac49 * (if greaterThreshold1.y then idealCommutingSwitch1.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_75(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,75};
  $P$res$P1$P$pDERLSJac49$PdummyVarLSJac49 = $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac49$PdummyVarLSJac49 - (($PidealCommutingSwitch1_s1SeedLSJac49) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */:1.0)));
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac49_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac49;
  PW_PowerSystem_eqFunction_72(data, threadData);

  PW_PowerSystem_eqFunction_73(data, threadData);

  PW_PowerSystem_eqFunction_74(data, threadData);

  PW_PowerSystem_eqFunction_75(data, threadData);
  
  TRACE_POP
  return 0;
}

/*
 equation index: 42
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n2._i._$pDERLSJac48._dummyVarLSJac48 = (-idealCommutingSwitch2_s2SeedLSJac48) * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Goff)
 */
void PW_PowerSystem_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac48$PdummyVarLSJac48 = ((-$PidealCommutingSwitch2_s2SeedLSJac48)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */));
  TRACE_POP
}

/*
 equation index: 43
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n1._i._$pDERLSJac48._dummyVarLSJac48 = (-idealCommutingSwitch2_s1SeedLSJac48) * (if convertToBoolean.y then idealCommutingSwitch2.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac48$PdummyVarLSJac48 = ((-$PidealCommutingSwitch2_s1SeedLSJac48)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */:1.0));
  TRACE_POP
}

/*
 equation index: 44
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._p._v._$pDERLSJac48._dummyVarLSJac48 = idealCommutingSwitch2_s1SeedLSJac48 * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Ron)
 */
void PW_PowerSystem_eqFunction_44(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,44};
  $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac48$PdummyVarLSJac48 = ($PidealCommutingSwitch2_s1SeedLSJac48) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */));
  TRACE_POP
}

/*
 equation index: 45
 type: SIMPLE_ASSIGN
 $res._1._$pDERLSJac48._dummyVarLSJac48 = idealCommutingSwitch2_s2SeedLSJac48 * (if convertToBoolean.y then idealCommutingSwitch2.Ron else 1.0) - idealCommutingSwitch2.p.v.$pDERLSJac48.dummyVarLSJac48
 */
void PW_PowerSystem_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  $P$res$P1$P$pDERLSJac48$PdummyVarLSJac48 = ($PidealCommutingSwitch2_s2SeedLSJac48) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */:1.0)) - $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac48$PdummyVarLSJac48;
  TRACE_POP
}

/*
 equation index: 46
 type: SIMPLE_ASSIGN
 $res._2._$pDERLSJac48._dummyVarLSJac48 = idealCommutingSwitch2.n2.i.$pDERLSJac48.dummyVarLSJac48 + idealCommutingSwitch2.n1.i.$pDERLSJac48.dummyVarLSJac48
 */
void PW_PowerSystem_eqFunction_46(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,46};
  $P$res$P2$P$pDERLSJac48$PdummyVarLSJac48 = $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac48$PdummyVarLSJac48 + $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac48$PdummyVarLSJac48;
  TRACE_POP
}
int PW_PowerSystem_functionJacLSJac48_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_LSJac48;
  PW_PowerSystem_eqFunction_42(data, threadData);

  PW_PowerSystem_eqFunction_43(data, threadData);

  PW_PowerSystem_eqFunction_44(data, threadData);

  PW_PowerSystem_eqFunction_45(data, threadData);

  PW_PowerSystem_eqFunction_46(data, threadData);
  
  TRACE_POP
  return 0;
}
int PW_PowerSystem_functionJacD_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_D;
  
  TRACE_POP
  return 0;
}
int PW_PowerSystem_functionJacC_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_C;
  
  TRACE_POP
  return 0;
}
int PW_PowerSystem_functionJacB_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_B;
  
  TRACE_POP
  return 0;
}
int PW_PowerSystem_functionJacA_column(void* inData, threadData_t *threadData)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = PW_PowerSystem_INDEX_JAC_A;
  
  TRACE_POP
  return 0;
}


