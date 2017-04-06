/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac53 5
  int PW_PowerSystem_functionJacLSJac53_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac53(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac53 */
#define $Pmotor_lesigma_vSeedLSJac53 data->simulationInfo->analyticJacobians[5].seedVars[0]
#define _$P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac53$PdummyVarLSJac53(i) data->simulationInfo->analyticJacobians[5].tmpVars[0]
#define $P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac53$PdummyVarLSJac53 _$P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac53$PdummyVarLSJac53(0)

#define _$Pmotor$PairGapDC$Pvei$P$pDERLSJac53$PdummyVarLSJac53(i) data->simulationInfo->analyticJacobians[5].tmpVars[1]
#define $Pmotor$PairGapDC$Pvei$P$pDERLSJac53$PdummyVarLSJac53 _$Pmotor$PairGapDC$Pvei$P$pDERLSJac53$PdummyVarLSJac53(0)

#define _$P$res$P1$P$pDERLSJac53$PdummyVarLSJac53(i) data->simulationInfo->analyticJacobians[5].resultVars[0]
#define $P$res$P1$P$pDERLSJac53$PdummyVarLSJac53 _$P$res$P1$P$pDERLSJac53$PdummyVarLSJac53(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac52 4
  int PW_PowerSystem_functionJacLSJac52_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac52(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac52 */
#define $PidealCommutingSwitch1_s2SeedLSJac52 data->simulationInfo->analyticJacobians[4].seedVars[0]
#define $PidealCommutingSwitch1_s1SeedLSJac52 data->simulationInfo->analyticJacobians[4].seedVars[1]
#define _$PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac52$PdummyVarLSJac52(i) data->simulationInfo->analyticJacobians[4].tmpVars[0]
#define $PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac52$PdummyVarLSJac52 _$PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac52$PdummyVarLSJac52(0)

#define _$Parm_sensor$Pp$Pv$P$pDERLSJac52$PdummyVarLSJac52(i) data->simulationInfo->analyticJacobians[4].tmpVars[1]
#define $Parm_sensor$Pp$Pv$P$pDERLSJac52$PdummyVarLSJac52 _$Parm_sensor$Pp$Pv$P$pDERLSJac52$PdummyVarLSJac52(0)

#define _$PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac52$PdummyVarLSJac52(i) data->simulationInfo->analyticJacobians[4].tmpVars[2]
#define $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac52$PdummyVarLSJac52 _$PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac52$PdummyVarLSJac52(0)

#define _$P$res$P2$P$pDERLSJac52$PdummyVarLSJac52(i) data->simulationInfo->analyticJacobians[4].resultVars[1]
#define $P$res$P2$P$pDERLSJac52$PdummyVarLSJac52 _$P$res$P2$P$pDERLSJac52$PdummyVarLSJac52(0)

#define _$P$res$P1$P$pDERLSJac52$PdummyVarLSJac52(i) data->simulationInfo->analyticJacobians[4].resultVars[0]
#define $P$res$P1$P$pDERLSJac52$PdummyVarLSJac52 _$P$res$P1$P$pDERLSJac52$PdummyVarLSJac52(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac51 3
  int PW_PowerSystem_functionJacLSJac51_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac51(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac51 */
#define $PidealCommutingSwitch2_s1SeedLSJac51 data->simulationInfo->analyticJacobians[3].seedVars[0]
#define $PidealCommutingSwitch2_s2SeedLSJac51 data->simulationInfo->analyticJacobians[3].seedVars[1]
#define _$PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac51$PdummyVarLSJac51(i) data->simulationInfo->analyticJacobians[3].tmpVars[0]
#define $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac51$PdummyVarLSJac51 _$PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac51$PdummyVarLSJac51(0)

#define _$PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac51$PdummyVarLSJac51(i) data->simulationInfo->analyticJacobians[3].tmpVars[1]
#define $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac51$PdummyVarLSJac51 _$PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac51$PdummyVarLSJac51(0)

#define _$PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac51$PdummyVarLSJac51(i) data->simulationInfo->analyticJacobians[3].tmpVars[2]
#define $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac51$PdummyVarLSJac51 _$PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac51$PdummyVarLSJac51(0)

#define _$P$res$P2$P$pDERLSJac51$PdummyVarLSJac51(i) data->simulationInfo->analyticJacobians[3].resultVars[1]
#define $P$res$P2$P$pDERLSJac51$PdummyVarLSJac51 _$P$res$P2$P$pDERLSJac51$PdummyVarLSJac51(0)

#define _$P$res$P1$P$pDERLSJac51$PdummyVarLSJac51(i) data->simulationInfo->analyticJacobians[3].resultVars[0]
#define $P$res$P1$P$pDERLSJac51$PdummyVarLSJac51 _$P$res$P1$P$pDERLSJac51$PdummyVarLSJac51(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac50 2
  int PW_PowerSystem_functionJacLSJac50_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac50(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac50 */
#define $Pmotor_airGapDC_veiSeedLSJac50 data->simulationInfo->analyticJacobians[2].seedVars[0]
#define _$P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac50$PdummyVarLSJac50(i) data->simulationInfo->analyticJacobians[2].tmpVars[0]
#define $P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac50$PdummyVarLSJac50 _$P$DER$Pmotor$Plesigma$Pi$P$pDERLSJac50$PdummyVarLSJac50(0)

#define _$Pmotor$Plesigma$Pv$P$pDERLSJac50$PdummyVarLSJac50(i) data->simulationInfo->analyticJacobians[2].tmpVars[1]
#define $Pmotor$Plesigma$Pv$P$pDERLSJac50$PdummyVarLSJac50 _$Pmotor$Plesigma$Pv$P$pDERLSJac50$PdummyVarLSJac50(0)

#define _$P$res$P1$P$pDERLSJac50$PdummyVarLSJac50(i) data->simulationInfo->analyticJacobians[2].resultVars[0]
#define $P$res$P1$P$pDERLSJac50$PdummyVarLSJac50 _$P$res$P1$P$pDERLSJac50$PdummyVarLSJac50(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac49 1
  int PW_PowerSystem_functionJacLSJac49_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac49(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac49 */
#define $PidealCommutingSwitch1_s2SeedLSJac49 data->simulationInfo->analyticJacobians[1].seedVars[0]
#define $PidealCommutingSwitch1_s1SeedLSJac49 data->simulationInfo->analyticJacobians[1].seedVars[1]
#define _$PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac49$PdummyVarLSJac49(i) data->simulationInfo->analyticJacobians[1].tmpVars[0]
#define $PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac49$PdummyVarLSJac49 _$PidealCommutingSwitch1$Pn1$Pi$P$pDERLSJac49$PdummyVarLSJac49(0)

#define _$Parm_sensor$Pp$Pv$P$pDERLSJac49$PdummyVarLSJac49(i) data->simulationInfo->analyticJacobians[1].tmpVars[1]
#define $Parm_sensor$Pp$Pv$P$pDERLSJac49$PdummyVarLSJac49 _$Parm_sensor$Pp$Pv$P$pDERLSJac49$PdummyVarLSJac49(0)

#define _$PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac49$PdummyVarLSJac49(i) data->simulationInfo->analyticJacobians[1].tmpVars[2]
#define $PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac49$PdummyVarLSJac49 _$PidealCommutingSwitch1$Pn2$Pi$P$pDERLSJac49$PdummyVarLSJac49(0)

#define _$P$res$P2$P$pDERLSJac49$PdummyVarLSJac49(i) data->simulationInfo->analyticJacobians[1].resultVars[1]
#define $P$res$P2$P$pDERLSJac49$PdummyVarLSJac49 _$P$res$P2$P$pDERLSJac49$PdummyVarLSJac49(0)

#define _$P$res$P1$P$pDERLSJac49$PdummyVarLSJac49(i) data->simulationInfo->analyticJacobians[1].resultVars[0]
#define $P$res$P1$P$pDERLSJac49$PdummyVarLSJac49 _$P$res$P1$P$pDERLSJac49$PdummyVarLSJac49(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_LSJac48 0
  int PW_PowerSystem_functionJacLSJac48_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianLSJac48(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac48 */
#define $PidealCommutingSwitch2_s1SeedLSJac48 data->simulationInfo->analyticJacobians[0].seedVars[0]
#define $PidealCommutingSwitch2_s2SeedLSJac48 data->simulationInfo->analyticJacobians[0].seedVars[1]
#define _$PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac48$PdummyVarLSJac48(i) data->simulationInfo->analyticJacobians[0].tmpVars[0]
#define $PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac48$PdummyVarLSJac48 _$PidealCommutingSwitch2$Pp$Pv$P$pDERLSJac48$PdummyVarLSJac48(0)

#define _$PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac48$PdummyVarLSJac48(i) data->simulationInfo->analyticJacobians[0].tmpVars[1]
#define $PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac48$PdummyVarLSJac48 _$PidealCommutingSwitch2$Pn1$Pi$P$pDERLSJac48$PdummyVarLSJac48(0)

#define _$PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac48$PdummyVarLSJac48(i) data->simulationInfo->analyticJacobians[0].tmpVars[2]
#define $PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac48$PdummyVarLSJac48 _$PidealCommutingSwitch2$Pn2$Pi$P$pDERLSJac48$PdummyVarLSJac48(0)

#define _$P$res$P2$P$pDERLSJac48$PdummyVarLSJac48(i) data->simulationInfo->analyticJacobians[0].resultVars[1]
#define $P$res$P2$P$pDERLSJac48$PdummyVarLSJac48 _$P$res$P2$P$pDERLSJac48$PdummyVarLSJac48(0)

#define _$P$res$P1$P$pDERLSJac48$PdummyVarLSJac48(i) data->simulationInfo->analyticJacobians[0].resultVars[0]
#define $P$res$P1$P$pDERLSJac48$PdummyVarLSJac48 _$P$res$P1$P$pDERLSJac48$PdummyVarLSJac48(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_D 9
  int PW_PowerSystem_functionJacD_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */
#define $Pdown_inputSeedD data->simulationInfo->analyticJacobians[9].seedVars[0]
#define $Pinput_torqueSeedD data->simulationInfo->analyticJacobians[9].seedVars[1]
#define $Pup_inputSeedD data->simulationInfo->analyticJacobians[9].seedVars[2]

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_C 8
  int PW_PowerSystem_functionJacC_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */
#define $Pmotor_airGapDC_psi_eSeedC data->simulationInfo->analyticJacobians[8].seedVars[0]
#define $Pmotor_inertiaRotor_wSeedC data->simulationInfo->analyticJacobians[8].seedVars[1]
#define $Pmotor_la_iSeedC data->simulationInfo->analyticJacobians[8].seedVars[2]
#define $Pmotor_phiMechanicalSeedC data->simulationInfo->analyticJacobians[8].seedVars[3]

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_B 7
  int PW_PowerSystem_functionJacB_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */
#define $Pdown_inputSeedB data->simulationInfo->analyticJacobians[7].seedVars[0]
#define $Pinput_torqueSeedB data->simulationInfo->analyticJacobians[7].seedVars[1]
#define $Pup_inputSeedB data->simulationInfo->analyticJacobians[7].seedVars[2]

#if defined(__cplusplus)
extern "C" {
#endif
  #define PW_PowerSystem_INDEX_JAC_A 6
  int PW_PowerSystem_functionJacA_column(void* data, threadData_t *threadData);
  int PW_PowerSystem_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */
#define $Pmotor_airGapDC_psi_eSeedA data->simulationInfo->analyticJacobians[6].seedVars[0]
#define $Pmotor_inertiaRotor_wSeedA data->simulationInfo->analyticJacobians[6].seedVars[1]
#define $Pmotor_la_iSeedA data->simulationInfo->analyticJacobians[6].seedVars[2]
#define $Pmotor_phiMechanicalSeedA data->simulationInfo->analyticJacobians[6].seedVars[3]


