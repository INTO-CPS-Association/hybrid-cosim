/* Internal types for Dymosim FMI implementation. */

#ifndef types_h
#define types_h

#include "conf.h"
#include <stdlib.h>

#define TIME_INFINITY 1e36

#ifdef FMI_2
#include "fmi2TypesPlatform.h"
#include "fmi2FunctionTypes.h"
#else
#include "fmiPlatformTypes_.h"
#include "fmiFunctions_.h"
#endif
#include "FMIversionPrefix.h"
/* for storing of result from within FMU */
#ifdef STORE_RESULT
#include "GenerateResultInNonDymosim.h"
#endif

#ifdef NEW_CODE_GENERATION
#include <dse_types.h>
#endif

#include "dsblock.h"

#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
/* Sundials */
#include <nvector/nvector_serial.h>
#include <sundials/sundials_direct.h>
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */

/* ----------------- type definitions ----------------- */

#ifndef FMI_2
typedef char fmiChar;		/*fmiChar not included in FMI 1, required for String allocation*/
#endif

typedef enum {
	iDemandStart,            /* Start of integration: Initial equations are solved. */
	iDemandOutput,           /* Compute outputs */
	iDemandDerivative,       /* Compute derivatives */
	iDemandVariable,         /* Compute auxiliary variables */
	iDemandCrossingFunction, /* Compute crossing functions */
	iDemandEventHandling,    /* Event handling */
	iDemandTerminal = 7      /* 'terminal()' is true. */
} IDemandLevel;

typedef enum {
	modelInstantiated,
	modelInitializationMode, /*inside get macro and therfore required to be deifned for fmi1 */
#ifdef FMI_2
	modelEventMode,
	modelEventMode2,    /* event iteration ongoing */
	modelEventModeExit, /* event iteration finished */
#endif
	modelContinousTimeMode,
	modelTerminated
} ModelStatus;

typedef enum {
	integrationOK,
	integrationError,
	integrationTerminate,
	integrationEvent
} IntegrationStatus;

typedef struct {
	/* Jacobian upper/lower bandwidth */
	int jacubw;
	int jaclbw;

	long steps;
	long intSteps;

	float psolveTime;
	float jacTimesVecTime;
	int JacCalls;
	int fCalls;
	float fTime;
	float gTime;
	float totTime;
	
	int rejSteps;
	int rejIntSteps;
	int rejFCalls;
	int rejJacCalls;
	float rejFTime;
} Statistics;

#ifdef SAVE_STATE_DSMODEL
typedef struct {
	Dymola_bool *QL_;
	double *QRel_;
	double *QM_;

	double *Qn_, *Qp_;
	double *Qscaled_;
	double *QZold_;
	Dymola_bool *Qenable_;

	Dymola_bool *QTimed_;
	double *QCheckIf_;

	double *NextSampleTime_;
	double *NextSampleTimeNew_;
	Dymola_bool *NextSampleAct_;
	Dymola_bool *NextSampleActNew_;

	Dymola_bool *QEvaluate_;
	Dymola_bool *QEvaluateNew_;
	double *helpvar;

	double *oldQZ_, *oldQZDummy_;
	double *oldQZ2_;
	double *oldQZ3_;

	double *Aux_; 
	int *QNLfunc;
	int *QNLjac;
	double *QPre_;
	double * *RefPre_;
	double *EqRemember1_;
	double *EqRemember2_;
} DsmodelData;
#endif /* SAVE_STATE_DSMODEL */

#ifdef SAVE_STATE_SUNDIALS
#include "../src/cvode/cvode_impl.h"
/* internal data necessary to expose due to lack of state saving support in API */
/* taken from CkpntMemRec */
typedef struct {
	/* Nordsieck History Array */
	N_Vector ck_zn[L_MAX];

	/* Step data */
	long int ck_nst;
	realtype ck_tretlast;
	int      ck_q;
	int      ck_qmax;
	int      ck_qprime;
	int      ck_qwait;
	int      ck_L;
	realtype ck_gammap;
	realtype ck_h;
	realtype ck_hprime;
	realtype ck_hscale;
	realtype ck_eta;
	realtype ck_etamax;
	realtype ck_tau[L_MAX+1];
	realtype ck_tq[NUM_TESTS+1];
	realtype ck_l[L_MAX];

	/* Saved values */
	realtype ck_saved_tq5;
} CVodeCheckPointData;
#endif

typedef struct {
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
	N_Vector y;
	void* cvode_mem;
#ifdef SAVE_STATE_SUNDIALS
	int cvode_called;
	CVodeCheckPointData ck_mem;
#endif /* SAVE_STATE_SUNDIALS */

	/* absolute tolerance */
	N_Vector abstol;
	/* error weight vector */
	N_Vector ewt;
	/* temporary space */
	N_Vector tmp1;
	N_Vector tmp2;

	DlsMat J;
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */

	/* for input derivatve handling */
	FMIReal derivativeTime;
	FMIReal* inputDerivatives;
	FMIReal* inputsT0;
	int useDerivatives;

	/* for output derivatve handling */
	FMIReal* outputsPrev;
	FMIReal timePrev;
	
	/* statistics */
	Statistics stat;
} IntegrationData;

/* result storing on file */
typedef struct {
	FMIReal time;
	FMIReal* parameters;
	FMIReal* states;
	FMIReal* derivatives;
	FMIReal* outputs;
	FMIReal* inputs;
	FMIReal* auxiliary;
} ResultValues;

typedef struct {
#ifdef STORE_RESULT
	struct DeclarePhase phase;
#endif
	/* last time for sample, possibly buffered */
	FMIReal lastSampleTime;
	/* last time for sample on file */
	FMIReal lastFileSampleTime;
	/* last neglected sample warning applies up to this time */
	FMIReal lastWarnTime;
	/* buffered values */
	ResultValues** buf;
	int curBufSize;
	int curStartIx;
	int curIx;
	int nUsed;
	/* whether have warned about forced flush */
	FMIBoolean flushWarned;
} Result;

#ifdef FMI_2
/* for fmiGetDirectionalDerivative */
typedef struct {
	int nJacA;
	int nJacB;
	int nJacC;
	int nJacD;
	double * jacA;
	double * jacB;
	double * jacC;
	double * jacD;

	size_t nJacV;
	size_t nJacZ;
	double* jacV;
	double* jacVTmp1;
	double* jacVTmp2;
	double* jacZ;
	double* jacZTmp1;
	double* jacZTmp2;
} JacobianData;
#endif /* FMI_2 */

typedef struct {
	FMIReal tStart;
	FMIBoolean StopTimeDefined;
	FMIReal tStop;
	FMIBoolean relativeToleranceDefined;
    FMIReal relativeTolerance;



	FMIBoolean isCoSim;

	FMIString instanceName;
	FMIBoolean loggingOn;

	size_t nStates;
	size_t nIn;
	size_t nOut;
	size_t nAux;
	size_t nPar;
	size_t nSPar;
	size_t nCross;

	FMIReal* states;
	FMIReal* parameters;
	FMIReal* derivatives;
	FMIReal* inputs;
	FMIReal* outputs;
	FMIReal* auxiliary;
	FMIReal* crossingFunctions;

	FMIReal* statesNominal;

	FMIChar** sParameters;
	FMIChar** tsParameters;

	FMIReal* oldStates; /*To check if state values have changed durin event*/

#ifdef SAVE_STATE_DSMODEL
	DsmodelData* dsModelData;
#endif

#ifdef NEW_CODE_GENERATION
	boolean_t boolVars;

	integer8_t int8Vars;
	uinteger8_t uint8Vars;
	integer16_t int16Vars;
	uinteger16_t uint16Vars;
	integer32_t int32Vars;
	uinteger32_t uint32Vars;
	integer64_t int64Vars;
	uinteger64_t uint64Vars;

	real_t realVars;
#endif /* NEW_CODE_GENERATION */

#ifdef FMI_2
	const FMICallbackFunctions* functions;
#else
	FMICallbackFunctions functions;
#endif

	FMIReal time;
	int icall;

	/* for buffering of short messages without linebreaks */
	char logbuf[256];
	char* logbufp;

	ModelStatus mStatus;
	/* only for FMI 2.0 really, but convenient internally also for 1.0 */
	FMIBoolean terminationByModel;

	/* for storing of result from within FMU */
	FMIBoolean storeResult;
	Result* result;

	struct BasicDDymosimStruct* dstruct;
	struct BasicIDymosimStruct* istruct;
	/* to avoid numerous castings */
	double* duser;
	int* iuser;

	/* for libdsdll */
	struct DymosimSimulator* sim;

	/* for internal integration */
	IntegrationData* iData;

	int allocDone;
	int valWasSet;
	int reinitRequired;
	int eventIterRequired;
	int recalJacobian;

#ifdef FMI_2
	/* for fmiGetDirectionalDerivative */
	JacobianData jacData;
	FMIBoolean firstEventCall;
#endif
	int eventIterationOnGoing;
	void**handles;
	int QiErr;
	struct DYNInstanceData* did;
	unsigned long long inlineStepCounter;
} Component;

#ifndef DYMOLA_TIMES
#define DYMOLA_TIMES
struct DymolaTimes {
	int num;
	double maxim;
	double minim;
	double total;
	int numAccum;
	double maximAccum;
	double minimAccum;
	double totalAccum;
	const char*name;
};
#endif


#endif /* types_h */
