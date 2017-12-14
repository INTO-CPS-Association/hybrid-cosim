/* The generic implementation of the FMI interface common for both ME and Co-simulation. */

/* need to include first so that correct files are included */
#include "conf.h"
#include "util.h"
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
#include "integration.h"
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */
#include "fmiFunctions_fwd.h"

#include "adymosim.h"
//#include <string.h>
#include <assert.h>
#include <math.h>

/* ----------------- macros ----------------- */

#define ALLOC_AND_CHECK(dest, n, size)    	     							\
	dest = allocateMemory(n, size);	                        				\
	if (dest == NULL) {														\
		goto mem_fail;                                                      \
	} else {																\
		freeList[freeIndex++] = dest;										\
	}

#define COPY_VARIABLES(source, target)                                                                    \
        memcpy(target->states, source->states, source->nStates * sizeof(FMIReal));                        \
		memcpy(target->derivatives, source->derivatives, source->nStates * sizeof(FMIReal));              \
		memcpy(target->parameters, source->parameters, source->nPar * sizeof(FMIReal));                   \
		memcpy(target->inputs, source->inputs, source->nIn * sizeof(FMIReal));                            \
		memcpy(target->outputs, source->outputs, source->nOut * sizeof(FMIReal));                         \
		memcpy(target->auxiliary, source->auxiliary, source->nAux * sizeof(FMIReal));                     \
		memcpy(target->crossingFunctions, source->crossingFunctions, source->nCross * sizeof(FMIReal));   \
		memcpy(target->statesNominal, source->statesNominal, source->nStates * sizeof(FMIReal));          \
		{                                                                                                 \
		  size_t i = 0;                                                                                   \
		  for(i = 0; i< target->nSPar; ++i){                                                              \
		    memcpy(target->sParameters[i], source->sParameters[i], (MAX_STRING_SIZE+1) * sizeof(FMIChar));\
			target->sParameters[i][MAX_STRING_SIZE]='\0';                                                 \
		  }                                                                                               \
		}

/* ----------------- local function declarations ----------------- */

/* find the largest iDemand value in a given array of value references */
static int getLargestIdemand(const FMIValueReference vr[], size_t nvr);

/* copy model variables, including the state nominals, from source to target component */
static void copyVariables(Component* source, Component* target);

/* ----------------- local variables ----------------- */

/* when compiling as a single complilation unit, this is already defined */
#ifndef FMU_SOURCE_SINGLE_UNIT
/* only supports single instances */
Component* globalComponent = NULL;
Component* globalComponent2 = NULL;
#endif

/* Global logger function used by DymosimMessage routines */
DYMOLA_STATIC void fmu_logger(const char* message, int newline, int severity) 
{
	char hashHandeldMessage[4096];
	FMIStatus stat=FMIError;
	int i = 0;
	int j = 0;
	Component* comp;

	switch (severity){
		case 0: stat = FMIOK; break; 
        case 1: stat = FMIWarning; break;
        case 2: stat = FMIError;   break;
	}
		
	for(; j<sizeof(hashHandeldMessage)-1;++i,++j){
		if(message[i]=='\0'){
			hashHandeldMessage[j]='\0';
			break;
		}
		if(message[i]=='#'){
			hashHandeldMessage[j++]='#';
		}
		hashHandeldMessage[j]=message[i];
	}
	hashHandeldMessage[sizeof(hashHandeldMessage)-1]='\0';
		
	comp = globalComponent;
	if (comp == NULL) comp=globalComponent2;
	if (comp != NULL) {
		if (newline) {
			util_logger(comp, comp->instanceName, stat, "", "%s", hashHandeldMessage);
		} else {
			util_buflogger(comp, comp->instanceName, stat, "", "%s", hashHandeldMessage);
		}
	}
}

/* ----------------- external variables ----------------- */

#ifndef DYMOLA_STATIC_IMPORT
#define DYMOLA_STATIC_IMPORT DYMOLA_STATIC
#endif

#ifdef SAVE_STATE_DSMODEL

extern int QJacobianCG_[];
extern int QJacobianGC_[];

extern Dymola_bool QL_[];
extern double QRel_[];
extern double QM_[];

extern double Qn_[], Qp_[];
extern double Qscaled_[];
extern double QZold_[];
extern Dymola_bool Qenable_[];

extern Dymola_bool QTimed_[];
extern double QCheckIf_[];

extern double NextSampleTime_[];
extern double NextSampleTimeNew_[];
extern Dymola_bool NextSampleAct_[];
extern Dymola_bool NextSampleActNew_[];

extern Dymola_bool QEvaluate_[];
extern Dymola_bool QEvaluateNew_[];
extern double helpvar[];

extern double oldQZ_[], oldQZDummy_[];
//#if SecondDegree
      extern double oldQZ2_[];
      extern double oldQZ3_[];
//#endif

extern double Aux_[];
extern int QNLfunc[];
extern int QNLjac[];
extern double QPre_[];
extern double * RefPre_[];
extern double EqRemember1_[];
extern double EqRemember2_[];
extern double EqRemember1Time_;
extern double EqRemember2Time_;
extern int MaxPreNr_;
extern int QNLmax;

#endif /* SAVE_STATE_DSMODEL */

/* ----------------- unexposed function definitions ----------------- */

/* Enable storing of result from within FMU */
DYMOLA_STATIC void __enableResultStoring(FMIComponent c) {
	Component* comp = (Component*) c;
	comp->storeResult = FMITrue;
}

/* ----------------- function definitions ----------------- */

/* For 1.0 it belongs to Co-sim interface only */
#ifdef FMI_2
DYMOLA_STATIC const char* fmiGetTypesPlatform_()
{
	return fmi2TypesPlatform;
}
#endif

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC const char* fmiGetVersion_()
{
	return fmiVersion;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSetDebugLogging_(FMIComponent c, FMIBoolean loggingOn
#ifdef FMI_2
, size_t nCategories, const FMIString categories[]
#endif
)
{
	Component* comp = (Component*) c;
	comp->loggingOn = loggingOn;
#ifdef FMI_2
	/* TODO: handle categories */
#endif
	return FMIOK;
}

#ifdef FMI_2
static FMIString initFuncName = "fmiEnterInitializationMode";
#else
static FMIString initFuncName = "fmiInitializeModel";
#endif

/* Common get macro */
#define FMI_GET(type, label, vr_label, m, vr, nvr, value, idemand) {                \
	Component* comp = (Component*) c;                                               \
	size_t i;                                                                       \
                                                                                    \
	if(comp->mStatus == modelInstantiated ){                                        \
		util_logger(comp, comp->instanceName, FMIWarning, "",                       \
		"fmiGet"#label": Not allowed before call of %s", initFuncName);             \
		return FMIWarning;                                                          \
	}                                                                               \
	                                                                                \
	if (comp->icall < idemand ||comp->icall == iDemandStart && comp->mStatus ==     \
	     modelInitializationMode && comp->valWasSet) {                              \
		 /* refresh cache */                                                        \
		int QiErr = 0;                                                              \
        /* TODO: how to handle dsblock for NEW_CODE_GENERATION? */                  \
        QiErr = util_refresh_cache(comp, idemand, NULL, NULL);                      \
		if (QiErr != 0) {                                                           \
		    FMIStatus status =                                                      \
			(QiErr == 1 && strcmp(#label, "Real") == 0) ? FMIDiscard : FMIError;    \
			util_logger(comp, comp->instanceName, status, "",                       \
			       "fmiGet"#label": dsblock_ failed, QiErr = %d", QiErr);           \
			HANDLE_STATUS_RETURN(status);                                           \
		}                                                                           \
	}                                                                               \
                                                                                    \
	for (i = 0; i < nvr; i++) {                                                     \
		const FMIValueReference r = vr[i];                                          \
		int ix = FMI_INDEX(r);                                                      \
                                                                                    \
		switch (FMI_CATEGORY(r)) {                                                  \
		case dsOutput:                                                              \
			value[i] = (type)comp->outputs[ix];                                     \
			break;                                                                  \
        case dsAux:                                                                 \
			value[i] = (type)comp->auxiliary[ix];                                   \
			break;                                                                  \
		case dsState:                                                               \
			value[i] = (type)comp->states[ix];                                      \
			break;                                                                  \
		case dsDerivative:                                                          \
			value[i] = (type)comp->derivatives[ix];                                 \
			break;                                                                  \
		case dsParameter:                                                           \
			value[i] = (type)comp->parameters[ix];                                  \
			break;                                                                  \
        case dsInput:                                                               \
			value[i] = (type)comp->inputs[ix];                                      \
			break;                                                                  \
		default:                                                                    \
			util_logger(comp, comp->instanceName, FMIWarning, "",                   \
			"fmiGet"#label": cannot get #"#vr_label"%u#", r);                       \
			return FMIWarning;                                                      \
		}                                                                           \
		util_logger(comp, comp->instanceName, FMIOK, "",                            \
		"fmiGet"#label": #"#vr_label"%u# = %g", r, (double) value[i]);              \
	}                                                                               \
} return FMIOK


/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiGetReal_(FMIComponent c, const FMIValueReference vr[], size_t nvr, FMIReal value[])
{
	int idemand = getLargestIdemand(vr, nvr);
#ifdef NEW_CODE_GENERATION
	return 0;
#else
	FMI_GET(FMIReal, Real, r, c, vr, nvr, value, idemand);
#endif
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiGetInteger_(FMIComponent c, const FMIValueReference vr[], size_t nvr, FMIInteger value[])
{
	int idemand = getLargestIdemand(vr, nvr);
	FMI_GET(FMIInteger, Integer, i, c, vr, nvr, value, idemand);
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiGetBoolean_(FMIComponent c, const FMIValueReference vr[], size_t nvr, FMIBoolean value[])
{
	int idemand = getLargestIdemand(vr, nvr);
	FMI_GET(FMIBoolean, Boolean, b, c, vr, nvr, value, idemand);
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiGetString_(FMIComponent c, const FMIValueReference vr[], size_t nvr, FMIString value[])
{
	Component* comp = (Component*) c;
	int idemand = getLargestIdemand(vr, nvr);
	size_t i;
	if(comp->mStatus == modelInstantiated ){
		util_logger(comp, comp->instanceName, FMIWarning, "",
			"fmiGetString: Not allowed before call of %s", initFuncName);
		return FMIWarning;
	}
	if (comp->icall < idemand || comp->mStatus == modelInitializationMode && comp->valWasSet) {                              
		int QiErr = 0;                                                             
        QiErr = util_refresh_cache(comp, idemand, NULL, NULL);
		if (QiErr != 0) {
			util_logger(comp, comp->instanceName, FMIError, "",
				"fmiGetString: dsblock_ failed, QiErr = %d", QiErr);
			HANDLE_STATUS_RETURN(FMIError);
		}
	}
	for ( i = 0; i < nvr; i++) {
		const FMIValueReference r = vr[i];
		int ix = FMI_INDEX(r);
		switch (FMI_CATEGORY(r)) {
		case dsStringParameter:
			value[i] = comp->sParameters[ix];
			break;
		default:
			util_logger(comp, comp->instanceName, FMIWarning, "", 
				"fmiGetString: cannot get #s%u#", r);
			return FMIWarning;
		}
		util_logger(comp, comp->instanceName, FMIOK, "",
			"fmiGetString: #s%u# = %s", r, (FMIString) value[i]);
	}

	return FMIOK;
}
#ifdef ONLY_INCLUDE_INLINE_INTEGRATION
#define integration_sync_extrapolation_input(a, b)
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */


/* ---------------------------------------------------------------------- */
/* Common set macro */
#define FMI_SET(label, vr_label, m, vr, nvr, value)                            \
    Component* comp = (Component*) c;                                          \
	size_t i;                                                                  \
    FMIBoolean allowed = FMITrue;                                              \
    FMIBoolean modified = FMIFalse;                                            \
                                                                               \
	for (i = 0; i < nvr; i++) {                                                \
		const FMIValueReference r = vr[i];                                     \
		int ix = FMI_INDEX(r);                                                 \
                                                                               \
		switch (FMI_CATEGORY(r)) {                                             \
        case dsInput:                                                          \
            if (comp->inputs[ix] != value[i]) {                                \
			    comp->inputs[ix] = value[i];                                   \
                modified = FMITrue;                                            \
			    if (comp->isCoSim) {                                           \
				    integration_sync_extrapolation_input(comp, ix);            \
			    }                                                              \
			}                                                                  \
			break;                                                             \
		case dsState:                                                          \
/* allow this to help our own master out, although not really legal */         \
/*		    if (comp->isCoSim && comp->mStatus != modelInstantiated) {       */\
/*                allowed = fmiFalse;                                        */\
/*			} else {                                                         */\
			    /* allow since equivalent with setContinuousStates */          \
                if (comp->states[ix] != value[i]) {                            \
				   comp->states[ix] = value[i];                                \
                   modified = FMITrue;                                         \
				}                                                              \
/*			} */                                                               \
			break;                                                             \
        case dsAux:                                                            \
		 /*Allow if inline since states have become aux at that time*/         \
		    if (comp->mStatus == modelInstantiated ||                          \
                comp->mStatus == modelInitializationMode ||                    \
				comp->istruct->mInlineIntegration ) {                          \
                if (comp->auxiliary[ix] != value[i]) {                         \
			       comp->auxiliary[ix] = value[i];                             \
                   modified = FMITrue;                                         \
				}                                                              \
			}else {                                                            \
                allowed = FMIFalse;                                            \
		 	}                                                                  \
			break;                                                             \
		case dsParameter:                                                      \
		    /* TODO: check extra bit in value reference whether tunable */     \
     		/*if (comp->mStatus == modelInstantiated || "tunable") {*/         \
			if (comp->parameters[ix] != value[i]) {                            \
			    comp->parameters[ix] = value[i];                               \
                modified = FMITrue;                                            \
				if (comp->istruct) comp->istruct->mParametersNr++;			   \
			}                                                                  \
			/*} else {*/                                                       \
            /*    allowed = fmiFalse;*/                                        \
			/*}*/															   \
			break;                                                             \
        case dsDerivative:                                                     \
		if (comp->mStatus == modelInstantiated) {                              \
                if (comp->derivatives[ix] != value[i]) {                       \
			       comp->derivatives[ix] = value[i];                           \
                   modified = FMITrue;                                         \
				}                                                              \
			} else {                                                           \
                allowed = FMIFalse;                                            \
			}                                                                  \
			break;                                                             \
        case dsOutput:                                                         \
     		if (comp->mStatus == modelInstantiated) {                          \
                if (comp->outputs[ix] != value[i]) {                           \
				   comp->outputs[ix] = value[i];                               \
                   modified = FMITrue;                                         \
				}                                                              \
			} else {                                                           \
                allowed = FMIFalse;                                            \
			}                                                                  \
			break;                                                             \
		default:                                                               \
	        util_logger(comp, comp->instanceName, FMIWarning, "",              \
			       "fmiSet"#label": cannot set #"#vr_label"%u#  ", r);         \
            return FMIWarning;                                                 \
		}                                                                      \
                                                                               \
		if (allowed == FMIFalse) {                                             \
			util_logger(comp, comp->instanceName, FMIWarning, "",              \
			       "fmiSet"#label": may not change #"#vr_label"%u# at this "   \
			       "stage, setting of variable ignored", r);                   \
			return FMIWarning;                                                 \
		}                                                                      \
		util_logger(comp, comp->instanceName, FMIOK, "",                       \
		"fmiSet"#label": #"#vr_label"%u# = %g", r, (double) value[i]);         \
	}                                                                          \
                                                                               \
    if (modified == FMITrue) {                                                 \
   	   comp->icall = iDemandStart;                                             \
	   comp->valWasSet = 1;                                                    \
	   comp->recalJacobian = 1;                                                \
	}                                                                          \
	return FMIOK                                                               

/* ---------------------------------------------------------------------- */


DYMOLA_STATIC FMIStatus fmiSetReal_(FMIComponent c, const FMIValueReference vr[], size_t nvr, const FMIReal value[])
{
	FMI_SET(Real, r, c, vr, nvr, value);
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSetInteger_(FMIComponent c, const FMIValueReference vr[], size_t nvr, const FMIInteger value[])
{
	FMI_SET(Integer, i, c, vr, nvr, value);
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSetBoolean_(FMIComponent c, const FMIValueReference vr[], size_t nvr, const FMIBoolean value[])
{
	FMI_SET(Boolean, b, c, vr, nvr, value);
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSetString_(FMIComponent c, const FMIValueReference vr[], size_t nvr, const FMIString  value[])
{
	Component* comp = (Component*) c;
	size_t i; 
	FMIBoolean allowed = FMITrue; 
	FMIBoolean modified = FMIFalse; 
	for (i = 0; i < nvr; i++) {
		size_t len;
		const FMIValueReference r = vr[i];
		int ix = FMI_INDEX(r);
		switch (FMI_CATEGORY(r)) { 
		case dsStringParameter:
			len=strlen(value[i]);
			if (len>MAX_STRING_SIZE) len=MAX_STRING_SIZE;
			memcpy((comp->sParameters)[ix], value[i], len+1);
			comp->sParameters[ix][MAX_STRING_SIZE]='\0';
			if (comp->istruct) comp->istruct->mParametersNr++;
			break;
		default:
			util_logger(comp, comp->instanceName, FMIWarning, "",
				"fmiSetString: cannot set #s%u#  ", r);
			return FMIWarning;
		}
		if (allowed == FMIFalse) {
			util_logger(comp, comp->instanceName, FMIWarning, "",
				"fmiSetString: may not change #s%u# at this stage", r);
			return FMIWarning;
		}
		util_logger(comp, comp->instanceName, FMIOK, "",
			"fmiSetString: #s%u# = %s", r, (FMIString) value[i]);
	}
	if (modified == FMITrue) {
		comp->icall = iDemandStart;
		comp->valWasSet = 1;
		comp->recalJacobian = 1;
	}
	return FMIOK;
}

#ifdef FMI_2
DYMOLA_STATIC_IMPORT size_t dyn_allowMultipleInstances;
DYMOLA_STATIC void DYNInitializeDid(struct DYNInstanceData*did_);

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiGetFMUstate_(FMIComponent c, FMIFMUstate* FMUstate)
{
	static FMIString label = "fmiGetFMUstate";
	Component* source = (Component*) c;
	Component* target;
	FMIStatus status;


	/* first handle part common for both Model exchange and co-simulation */

	void* freeList[128];
	/*TODO suppot for manny Strings*/
	int freeIndex = 0;
	FMICallbackAllocateMemory allocateMemory = source->functions->allocateMemory;

	util_logger(source, source->instanceName, FMIOK, "", label);
	if (*FMUstate == NULL) {
		ALLOC_AND_CHECK(*FMUstate, 1, sizeof(Component));
		target = (Component*) *FMUstate;
		target->iData = NULL;
		target->allocDone = 0;
	} else {
		target = (Component*) *FMUstate;
	}

	/* get state vectors, derivatives, etc */
	{
		if (!target->allocDone) {
			size_t i =0;
			target->nStates = source->nStates;
			target->nPar = source->nPar;
			target->nIn = source->nIn;
			target->nOut = source->nOut;
			target->nAux = source->nAux;
			target->nCross = source->nCross;
			target->nSPar = source->nSPar;

			ALLOC_AND_CHECK(target->states, source->nStates + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->derivatives, source->nStates + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->parameters, source->nPar + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->inputs, source->nIn + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->outputs, source->nOut + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->auxiliary, source->nAux + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->crossingFunctions, source->nCross + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->statesNominal, source->nStates + 1, sizeof(FMIReal));
			ALLOC_AND_CHECK(target->sParameters, source->nSPar + 1, sizeof(FMIChar*));
			for(i = 0; i<target->nSPar; ++i){
				ALLOC_AND_CHECK(target->sParameters[i], MAX_STRING_SIZE+1, sizeof(FMIChar));
			}
			target->sParameters[target->nSPar]=NULL;
		}
		COPY_VARIABLES(source, target);
	}

	target->time = source->time;
	target->icall = source->icall;
	target->mStatus = source->mStatus;

	if (!target->allocDone) {
		ALLOC_AND_CHECK(target->dstruct, 1, sizeof(struct BasicDDymosimStruct));
		ALLOC_AND_CHECK(target->istruct, 1, sizeof(struct BasicIDymosimStruct));
	}
	memcpy(target->dstruct, source->dstruct, sizeof(struct BasicDDymosimStruct));
	memcpy(target->istruct, source->istruct, sizeof(struct BasicIDymosimStruct));

	if(!target->allocDone){
		if(dyn_allowMultipleInstances){
			ALLOC_AND_CHECK(target->did, 1, dyn_allowMultipleInstances);
			DYNInitializeDid(target->did);
		}else{
			target->did=NULL;
		}
	}
	if(target->did && dyn_allowMultipleInstances && source->did){
		memcpy(target->did, source->did, dyn_allowMultipleInstances);
	}
#ifdef SAVE_STATE_DSMODEL
	{
		int nrel_, ntim_, ncheckif_, nsamp_, nwhen_, nglobalhelp_, maxaux, qnlmax_, sizepre_, sizeeq_;
		DsmodelData* dsData;

		GetDimensions3(&nrel_, &ntim_, &ncheckif_, &nsamp_, &nwhen_, 
			&nglobalhelp_, &maxaux, &qnlmax_, &sizepre_, &sizeeq_);

		if (!target->allocDone) {
			ALLOC_AND_CHECK(dsData, 1, sizeof(DsmodelData));

			ALLOC_AND_CHECK(dsData->QL_, nrel_ + 1, sizeof(Dymola_bool));
			ALLOC_AND_CHECK(dsData->QRel_, nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->QM_, nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->Qn_, nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->Qp_, nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->Qscaled_, nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->QZold_, 2 * nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->Qenable_, nrel_ + 1, sizeof(Dymola_bool));

			ALLOC_AND_CHECK(dsData->QTimed_, ntim_ + 1, sizeof(Dymola_bool));
			ALLOC_AND_CHECK(dsData->QCheckIf_, ncheckif_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->NextSampleTime_, nsamp_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->NextSampleTimeNew_, nsamp_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->NextSampleAct_, nsamp_ + 1, sizeof(Dymola_bool));
			ALLOC_AND_CHECK(dsData->NextSampleActNew_, nsamp_ + 1, sizeof(Dymola_bool));

			ALLOC_AND_CHECK(dsData->QEvaluate_, nwhen_ + 1, sizeof(Dymola_bool));
			ALLOC_AND_CHECK(dsData->QEvaluateNew_, nwhen_ + 1, sizeof(Dymola_bool));
			ALLOC_AND_CHECK(dsData->helpvar, nglobalhelp_ + 1, sizeof(double));

			ALLOC_AND_CHECK(dsData->oldQZ_, 2 * nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->oldQZDummy_, 2 * nrel_ + 1, sizeof(double));	

			ALLOC_AND_CHECK(dsData->oldQZ2_, 2 * nrel_ + 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->oldQZ3_, 2 * nrel_ + 1, sizeof(double));

			ALLOC_AND_CHECK(dsData->Aux_, maxaux+10000, sizeof(double));
			ALLOC_AND_CHECK(dsData->QNLfunc, qnlmax_ ? qnlmax_ : 1, sizeof(int));
			ALLOC_AND_CHECK(dsData->QNLjac, qnlmax_ ? qnlmax_ : 1, sizeof(int));

			ALLOC_AND_CHECK(dsData->QPre_, sizepre_ ? sizepre_ : 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->RefPre_, sizepre_ ? sizepre_ : 1, sizeof(double));

			ALLOC_AND_CHECK(dsData->EqRemember1_, sizeeq_ ? sizeeq_ : 1, sizeof(double));
			ALLOC_AND_CHECK(dsData->EqRemember2_, sizeeq_ ? sizeeq_ : 1, sizeof(double));

			target->dsModelData = dsData;
		} else {
			dsData = target->dsModelData;
		}

		memcpy(dsData->QL_, QL_, nrel_ * sizeof(Dymola_bool));
		memcpy(dsData->QRel_, QRel_, nrel_ * sizeof(double));
		memcpy(dsData->QM_, QM_, nrel_ * sizeof(double));
		memcpy(dsData->Qn_, Qn_, nrel_ * sizeof(double));
		memcpy(dsData->Qp_, Qp_, nrel_ * sizeof(double));
		memcpy(dsData->Qscaled_, Qscaled_, nrel_ * sizeof(double));
		memcpy(dsData->QZold_, QZold_, 2 * nrel_ * sizeof(double));
		memcpy(dsData->Qenable_, Qenable_, nrel_ * sizeof(Dymola_bool));

		memcpy(dsData->QTimed_, QTimed_, ntim_ * sizeof(Dymola_bool));
		memcpy(dsData->QCheckIf_, QCheckIf_, ncheckif_ * sizeof(double));
		memcpy(dsData->NextSampleTime_, NextSampleTime_, nsamp_ * sizeof(double));
		memcpy(dsData->NextSampleTimeNew_, NextSampleTimeNew_, nsamp_ * sizeof(double));
		memcpy(dsData->NextSampleAct_, NextSampleAct_, nsamp_ * sizeof(Dymola_bool));
		memcpy(dsData->NextSampleActNew_, NextSampleActNew_, nsamp_ * sizeof(Dymola_bool));

		memcpy(dsData->QEvaluate_, QEvaluate_, nwhen_ * sizeof(Dymola_bool));
		memcpy(dsData->QEvaluateNew_, QEvaluateNew_, nwhen_ * sizeof(Dymola_bool));
		memcpy(dsData->helpvar, helpvar, nglobalhelp_ * sizeof(double));

		memcpy(dsData->oldQZ_, oldQZ_, 2 * nrel_ * sizeof(double));
		memcpy(dsData->oldQZDummy_, oldQZDummy_, 2 * nrel_ * sizeof(double));

		memcpy(dsData->oldQZ2_, oldQZ2_, 2 * nrel_ * sizeof(double));
		memcpy(dsData->oldQZ3_, oldQZ3_, 2 * nrel_ * sizeof(double));

		memcpy(dsData->Aux_, Aux_, (maxaux + 10000) * sizeof(double));
		memcpy(dsData->QNLfunc, QNLfunc, qnlmax_ * sizeof(int));
		memcpy(dsData->QNLjac, QNLjac, qnlmax_ * sizeof(int));

		memcpy(dsData->QPre_, QPre_, sizepre_ * sizeof(double));
		memcpy(dsData->RefPre_, RefPre_, sizepre_ * sizeof(double*));

		memcpy(dsData->EqRemember1_, EqRemember1_, sizeeq_ * sizeof(double));
		memcpy(dsData->EqRemember2_, EqRemember2_, sizeeq_ * sizeof(double));
	}
#endif /* SAVE_STATE_DSMODEL */

	/* then handle co-simulation specific part */
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
	if (source->isCoSim && !source->istruct->mInlineIntegration) {
		status = integration_get_state(source, target);
		if (status == FMIOK) {
			target->allocDone = 1;
			return FMIOK;
		} else {
			util_logger(c, source->instanceName, FMIError, "", "fmiGetFMUstate failed");
			return util_error(source);
		}
	}
#endif
	target->allocDone = 1;
	util_logger(source, source->instanceName, FMIOK, "", "%s", label);
	return FMIOK;

mem_fail:
	{
		int i;
		util_logger(source, source->instanceName, FMIError, "", "memory allocation failed");
		for (i = freeIndex - 1; i >= 0; i--) {
			source->functions->freeMemory(freeList[i]);
		}
		*FMUstate = NULL;
		return util_error(c);
	}

}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSetFMUstate_(FMIComponent c, FMIFMUstate FMUstate)
{
	static FMIString label = "fmiSetFMUstate";
	Component* target = (Component*) c;
	Component* source;
	/* first handle part common for both Model exchange and co-simulation */
	if (FMUstate == NULL) {
		util_logger(target, target->instanceName, FMIWarning, "", "fmiSetFMUstate: FMUstate == NULL");
		return FMIWarning;
	}
	source = (Component*) FMUstate;
	assert(source->allocDone);

	/* set state vectors, derivatives, etc */
	{
		COPY_VARIABLES(source, target);
	}
	if (source->time > target->time) {
		util_logger(target, target->instanceName, FMIWarning, "",
			"%s: Time in FMU state later than current. The behaviour for this is not well tested.",label);
	}
	target->time = source->time;
	target->icall = source->icall;
	target->mStatus = source->mStatus;
	
	memcpy(target->dstruct, source->dstruct, sizeof(struct BasicDDymosimStruct));
	memcpy(target->istruct, source->istruct, sizeof(struct BasicIDymosimStruct));
	if(target->did && source->did && dyn_allowMultipleInstances){
		memcpy(target->did, source->did, dyn_allowMultipleInstances);
	}
#ifdef SAVE_STATE_DSMODEL
	{
		int nrel_, ntim_, ncheckif_, nsamp_, nwhen_, nglobalhelp_, maxaux, qnlmax_, sizepre_, sizeeq_;
		DsmodelData* dsData = source->dsModelData; 
		GetDimensions3(&nrel_, &ntim_, &ncheckif_, &nsamp_, &nwhen_, 
			&nglobalhelp_, &maxaux, &qnlmax_, &sizepre_, &sizeeq_);

		memcpy(QL_, dsData->QL_, nrel_ * sizeof(Dymola_bool));
		memcpy(QRel_, dsData->QRel_, nrel_ * sizeof(double));
		memcpy(QM_, dsData->QM_, nrel_ * sizeof(double));
		memcpy(Qn_, dsData->Qn_, nrel_ * sizeof(double));
		memcpy(Qp_, dsData->Qp_, nrel_ * sizeof(double));
		memcpy(Qscaled_, dsData->Qscaled_, nrel_ * sizeof(double));
		memcpy(QZold_, dsData->QZold_, 2 * nrel_ * sizeof(double));
		memcpy(Qenable_, dsData->Qenable_, nrel_ * sizeof(Dymola_bool));

		memcpy(QTimed_, dsData->QTimed_, ntim_ * sizeof(Dymola_bool));
		memcpy(QCheckIf_, dsData->QCheckIf_, ncheckif_ * sizeof(double));
		memcpy(NextSampleTime_, dsData->NextSampleTime_, nsamp_ * sizeof(double));
		memcpy(NextSampleTimeNew_, dsData->NextSampleTimeNew_, nsamp_ * sizeof(double));
		memcpy(NextSampleAct_, dsData->NextSampleAct_, nsamp_ * sizeof(Dymola_bool));
		memcpy(NextSampleActNew_, dsData->NextSampleActNew_, nsamp_ * sizeof(Dymola_bool));

		memcpy(QEvaluate_, dsData->QEvaluate_, nwhen_ * sizeof(Dymola_bool));
		memcpy(QEvaluateNew_, dsData->QEvaluateNew_, nwhen_ * sizeof(Dymola_bool));
		memcpy(helpvar, dsData->helpvar, nglobalhelp_ * sizeof(double));

		memcpy(oldQZ_, dsData->oldQZ_, 2 * nrel_ * sizeof(double));
		memcpy(oldQZDummy_, dsData->oldQZDummy_, 2 * nrel_ * sizeof(double));

		memcpy(oldQZ2_, dsData->oldQZ2_, 2 * nrel_ * sizeof(double));
		memcpy(oldQZ3_, dsData->oldQZ3_, 2 * nrel_ * sizeof(double));

		memcpy(Aux_, dsData->Aux_, (maxaux + 10000) * sizeof(double));
		memcpy(QNLfunc, dsData->QNLfunc, qnlmax_ * sizeof(int));
		memcpy(QNLjac, dsData->QNLjac, qnlmax_ * sizeof(int));

		memcpy(QPre_, dsData->QPre_, sizepre_ * sizeof(double));
		memcpy(RefPre_, dsData->RefPre_, sizepre_ * sizeof(double*));

		memcpy(EqRemember1_, dsData->EqRemember1_, sizeeq_ * sizeof(double));
		memcpy(EqRemember2_, dsData->EqRemember2_, sizeeq_ * sizeof(double));
	}
#endif /* SAVE_STATE_DSMODEL */

	/* then handle co-simulation specific part */
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
	if (source->isCoSim && !source->istruct->mInlineIntegration) {
		return integration_set_state(source, target);
	}
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */
#if 0
	status = util_event_update(target, FMIFalse, &terminateSimulation);
	if (status != FMIOK) {
		util_logger(target, target->instanceName, status, "", "%s: failed with event iteration", label);
		return status;
	}
	if (terminateSimulation)  {
		util_logger(target, target->instanceName, status, "", "%s: simulation terminated by model", label);
		target->terminationByModel = FMITrue;
		return status;
	}
#endif
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
	if(target->isCoSim && !target->istruct->mInlineIntegration){
		if (integration_reinit(target) != integrationOK) {
			return util_error(target);
		}
	}
#endif
	util_logger(target, target->instanceName, FMIOK, "", "%s", label);
	return FMIOK;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiFreeFMUstate_(FMIComponent c, FMIFMUstate* FMUstate)
{

	static FMIString label = "fmiFreeFMUstate";
	Component* comp = (Component*) c;
	Component* target;
	FMICallbackFreeMemory freeMemory;
	int i;

	if (FMUstate == NULL || *FMUstate == NULL) {
		return FMIOK;
	}
	target = (Component*) *FMUstate;

	/* first handle part common for both Model exchange and co-simulation */

	freeMemory = comp->functions->freeMemory;

	freeMemory(target->states);
	freeMemory(target->derivatives);
	freeMemory(target->parameters);
	freeMemory(target->inputs);
	freeMemory(target->outputs);
	freeMemory(target->auxiliary);
	freeMemory(target->crossingFunctions);
	freeMemory(target->statesNominal);
	for(i = (int) comp->nSPar-1; i >=0; --i){
		freeMemory( (target->sParameters)[i]);
	}
	freeMemory(target->sParameters);
	freeMemory(target->dstruct);
	freeMemory(target->istruct);
	freeMemory(target->did);
#ifdef SAVE_STATE_DSMODEL
	if (target->dsModelData != NULL) {
		DsmodelData* dsData = target->dsModelData;

		freeMemory(dsData->QL_);
		freeMemory(dsData->QRel_);
		freeMemory(dsData->QM_);
		freeMemory(dsData->Qn_);
		freeMemory(dsData->Qp_);
		freeMemory(dsData->Qscaled_);
		freeMemory(dsData->QZold_);
		freeMemory(dsData->Qenable_);

		freeMemory(dsData->QTimed_);
		freeMemory(dsData->QCheckIf_);
		freeMemory(dsData->NextSampleTime_);
		freeMemory(dsData->NextSampleTimeNew_);
		freeMemory(dsData->NextSampleAct_);
		freeMemory(dsData->NextSampleActNew_);

		freeMemory(dsData->QEvaluate_);
		freeMemory(dsData->QEvaluateNew_);
		freeMemory(dsData->helpvar);

		freeMemory(dsData->oldQZ_);
		freeMemory(dsData->oldQZDummy_);	

		freeMemory(dsData->oldQZ2_);
		freeMemory(dsData->oldQZ3_);

		freeMemory(dsData->Aux_);
		freeMemory(dsData->QNLfunc);
		freeMemory(dsData->QNLjac);

		freeMemory(dsData->QPre_);
		freeMemory(dsData->RefPre_);

		freeMemory(dsData->EqRemember1_);
		freeMemory(dsData->EqRemember2_);

		freeMemory(dsData);
	}
#endif /* SAVE_STATE_DSMODEL */

	/* then handle co-simulation specific part */
#ifndef ONLY_INCLUDE_INLINE_INTEGRATION
	if (comp->isCoSim && !comp->istruct->mInlineIntegration) {
		integration_free_state(c, target);
	}
#endif /* ONLY_INCLUDE_INLINE_INTEGRATION */
	freeMemory(*FMUstate);
	*FMUstate = NULL;
	util_logger(comp, comp->instanceName, FMIOK, "", "%s", label);
	return FMIOK;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSerializedFMUstateSize_(FMIComponent c, FMIFMUstate FMUstate, 
												   size_t *size)
{
	Component* comp = (Component*) c;
	util_logger(comp, comp->instanceName, FMIWarning, "", "fmiSerializedFMUstateSize: not supported");
	return FMIWarning;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiSerializeFMUstate_(FMIComponent c, FMIFMUstate FMUstate,
											  FMIByte* serializedState, size_t size)
{
	Component* comp = (Component*) c;
	util_logger(comp, comp->instanceName, FMIWarning, "", "fmiSerializeFMUstate: not supported");
	return FMIWarning;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC FMIStatus fmiDeSerializeFMUstate_(FMIComponent c, 
								  const FMIByte serializedState[],
								  size_t size, FMIFMUstate* FMUstate)
{
	Component* comp = (Component*) c;
	util_logger(comp, comp->instanceName, FMIWarning, "", "fmiDeSerializeFMUstate: not supported");
	return FMIWarning;
}

/* ---------------------------------------------------------------------- */
DYMOLA_STATIC void SetDymolaJacobianPointers(struct DYNInstanceData*did_, double * QJacobian_,double * QBJacobian_,double * QCJacobian_,double * QDJacobian_,int QJacobianN_,
	int QJacobianNU_,int QJacobianNY_,double * QJacobianSparse_,int * QJacobianSparseR_,int * QJacobianSparseC_,int QJacobianNZ_);
DYMOLA_STATIC FMIStatus fmiGetDirectionalDerivative_(FMIComponent c,
													 const FMIValueReference z_ref[],
													 size_t nz,
													 const FMIValueReference v_ref[],
													 size_t nv,
													 const FMIReal dv[],
													 FMIReal dz[])
{
	static FMIString label = "fmiGetDirectionalDerivative";

	size_t i;
	size_t j;
	Component* comp = (Component*) c;
	FMIStatus status = FMIOK;

	FMICallbackAllocateMemory allocateMemory = comp->functions->allocateMemory;
	FMICallbackFreeMemory freeMemory = comp->functions->freeMemory;
	JacobianData* jacData = &comp->jacData;
	extern int QJacobianDefined_;
	util_logger(comp, comp->instanceName, FMIOK, "", "%s", label);
	LOG(comp, FMIOK, label);

	for (i = 0; i < nz; i++) {
		dz[i] = 0;
	}
	
	/*  analytic Jacobian available ? */
	if (QJacobianDefined_ && (comp->mStatus != modelInstantiated ||
		comp->mStatus != modelInitializationMode) ) {
			/*Analytical Jacobians are only valid after intialization*/
		int nx, nx2, nu, ny, nw, np, nrel, ncons, dae;
		int nA, nB, nC, nD;
		
		GetDimensions(&nx, &nx2, &nu, &ny, &nw, &np, &nrel, &ncons, &dae);

		nA = nx * nx;
		nB = nx * nu;
		nC = ny * nx;
		nD = ny * nu;

		/* avoid re-allocation on each call */
		if (jacData->nJacA < nA || jacData->jacA == NULL) {
			freeMemory(jacData->jacA);
			jacData->jacA = (double*) allocateMemory(nA+1, sizeof(double));
		}
		if (jacData->nJacB < nB || jacData->jacB == NULL) {
			freeMemory(jacData->jacB);
			jacData->jacB = (double*) allocateMemory(nB+1, sizeof(double));
		}
		if (jacData->nJacC < nC || jacData->jacC == NULL) {
			freeMemory(jacData->jacC);
			jacData->jacC = (double*) allocateMemory(nC+1, sizeof(double));
		}
		if (jacData->nJacD < nD || jacData->jacD == NULL) {
			freeMemory(jacData->jacD);
			jacData->jacD = (double*) allocateMemory(nD+1, sizeof(double));
		}

		if (jacData->jacA == NULL || jacData->jacB == NULL || jacData->jacC== NULL || jacData->jacD == NULL) {
			util_logger(comp, comp->instanceName, FMIError, "", "%s: memory allocation failed", label);
			status = FMIError;
			goto done1;
		}

		jacData->nJacA = nA;
		jacData->nJacB = nB;
		jacData->nJacC = nC;
		jacData->nJacD = nD;		


		if(comp->icall < iDemandDerivative || comp->recalJacobian){
			SetDymolaJacobianPointers(comp->did, jacData->jacA, jacData->jacB, jacData->jacC, jacData->jacD, nx, nu, ny, 0, 0,0,0);
			if (util_refresh_cache(comp, iDemandDerivative, label, NULL)) {
				status = FMIError;
				goto done1;
			}
			comp->recalJacobian = 0;
		}



		for (j = 0; j < nv; j++) {
			/* skip for seed == 0 */
			if (dv[j] != 0) {
				FMIBoolean vIsState = FMITrue;
				int v_ix = FMI_INDEX(v_ref[j]);

				/* determine type for v reference*/
				dsCategory v_cat = FMI_CATEGORY(v_ref[j]);
				switch(v_cat) {
				case dsState:
					assert(v_ix < nx);
					break;
				case dsInput:
					assert(v_ix < nu);
					vIsState = FMIFalse;
					break;
				default:
					util_logger(comp, comp->instanceName, FMIError, "",
						"%s: v_ref[%d] refers neither to state nor input", label, i);
					status = FMIError;
					goto done1;
				}

				/* Compute column j */
				for (i = 0; i < nz; i++) {
					/* figure out which of A, B, C and D matrix to fetch from */
					dsCategory z_cat = FMI_CATEGORY(z_ref[i]);
					int z_ix = FMI_INDEX(z_ref[i]);
					switch (z_cat) {
					case dsDerivative:
						assert(z_ix < nx);
						if (vIsState == FMITrue) {
							dz[i] += dv[j] * jacData->jacA[z_ix + v_ix * nx];
						} else {
							dz[i] += dv[j] * jacData->jacB[z_ix + v_ix * nx];
						}
						break;
					case dsOutput:
						assert(z_ix < ny);
						if (vIsState == FMITrue) {
							dz[i] += dv[j] * jacData->jacC[z_ix + v_ix * ny];
						} else {
							dz[i] += dv[j] * jacData->jacD[z_ix + v_ix * ny];
						}
						break;
					default:
						util_logger(comp, comp->instanceName, FMIError, "",
							"%s: z_ref[%d] refers neither to state derivative nor output", label, i);
						status = FMIError;
						goto done1;
					}
				}
			}
		}

done1:
		SetDymolaJacobianPointers(comp->did, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0);
		HANDLE_STATUS_RETURN(status);
	}

	/*  analytic Jacobian not available */
	{

		double *jacV;
		double *jacVTmp1;
		double *jacVTmp2;
		double *jacZ;
		double *jacZTmp1;
		double *jacZTmp2;
		double h;
		FMIBoolean success1;
		FMIBoolean success2;
		comp->istruct->mInJacobian=1;
		/* avoid re-allocation on each call */
		if (jacData->nJacV < nv) {
			freeMemory(jacData->jacV);
			freeMemory(jacData->jacVTmp1);
			freeMemory(jacData->jacVTmp2);
			jacData->jacV = (double*) allocateMemory(nv, sizeof(double));
			jacData->jacVTmp1 = (double*) allocateMemory(nv, sizeof(double));
			jacData->jacVTmp2 = (double*) allocateMemory(nv, sizeof(double));
		}
		if (jacData->nJacZ < nz) {
			freeMemory(jacData->jacZ);
			freeMemory(jacData->jacZTmp1);
			freeMemory(jacData->jacZTmp2);
			jacData->jacZ = (double*) allocateMemory(nz, sizeof(double));
			jacData->jacZTmp1 = (double*) allocateMemory(nz, sizeof(double));
			jacData->jacZTmp2 = (double*) allocateMemory(nz, sizeof(double));
		}

		if (jacData->jacV == NULL || jacData->jacVTmp1 == NULL || jacData->jacVTmp2 == NULL || 
			jacData->jacZ == NULL || jacData->jacZTmp1 == NULL || jacData->jacZTmp2 == NULL) {
			util_logger(comp, comp->instanceName, FMIError, "", "%s: memory allocation failed", label);
			status = FMIError;
			goto done2;
		}

		jacData->nJacV = nv;
		jacData->nJacZ = nz;

		/* save current v_values for later restoring */
		if ((status = fmiGetReal_(c, v_ref, nv, jacData->jacV)) != FMIOK ||
			(status = fmiGetReal_(c, z_ref, nz, jacData->jacZ)) != FMIOK) {
				goto done2;
		}

		jacV = jacData->jacV;
		jacVTmp1 = jacData->jacVTmp1;
		jacVTmp2 = jacData->jacVTmp2;
		jacZ = jacData->jacZ;
		jacZTmp1 = jacData->jacZTmp1;
		jacZTmp2 = jacData->jacZTmp2;

		h=1e6;
		for(i=0; i < nv; ++i ){
			if( dv[i] != 0 ){
				double temp = ( fabs(jacV[i]) + 1.0 ) * 1.0e-5 / fabs(dv[i]);
				if( temp < h )
					h=temp;
			}
		}

		/* perturb each state/continuous input */
		for (i = 0; i < nv; i++) {
			/* skip for seed == 0 */
			if (dv[i] != 0) {
				jacVTmp1[i] = jacV[i] + h*dv[i];
				jacVTmp2[i] = jacV[i] - h*dv[i];
			}else{
				jacVTmp1[i]=jacVTmp2[i]=jacV[i];
				
			}
		}
		if ((status = fmiSetReal_(c, v_ref, nv, jacVTmp1)) != FMIOK ) {
				goto done2;
		}
		status = fmiGetReal_(c, z_ref, nz, jacZTmp1);
		success1 = status == FMIOK;
		if ((status = fmiSetReal_(c, v_ref, nv, jacVTmp2)) != FMIOK ) {
				goto done2;
		}
		status = fmiGetReal_(c, z_ref, nz, jacZTmp2);
		success2 = status == FMIOK;

		if(success1 && success2){
			/*Central Difference*/
			for (i = 0; i < nz; i++) {
				dz[i] =  (FMIReal) (jacZTmp1[i] - jacZTmp2[i]) / (2.0 * h);
			}
		}else if(success1){
			/*Forwad Difference*/
			for (i = 0; i < nz; i++) {
				dz[i] =  (FMIReal) (jacZTmp1[i] - jacZ[i]) / h;
			}
		}else if(success2){
			/*Backward Difference*/
			for (i = 0; i < nz; i++) {
				dz[i] =  (FMIReal) ( jacZ[i]- jacZTmp2[i]) / h;
			}
		}else{
			goto done2;
		}
		/* Restore */
		if ((status = fmiSetReal_(c, v_ref, 1, jacV)) != FMIOK) {
			goto done2;
		}

done2:
		comp->istruct->mInJacobian=0;
		HANDLE_STATUS_RETURN(status);
	}
}
/* Wrapper functions for merging CS and ME functions with fmi 2 RC1 */

DYMOLA_STATIC FMIComponent fmiInstantiate_(FMIString instanceName, FMIType fmuType, FMIString fmuGUID, FMIString fmuResourceLocation, const FMICallbackFunctions* functions, FMIBoolean visible, FMIBoolean loggingOn){

	Component* comp;
	if(fmuType==FMICoSimulation){
		comp = (Component*) fmiInstantiateSlave_(instanceName, fmuGUID, fmuResourceLocation, functions, visible, loggingOn);
		if(comp)
			comp->isCoSim = FMITrue;
	}else if(fmuType==FMIModelExchange){
		comp = (Component*) fmiInstantiateModel_(instanceName, fmuGUID, fmuResourceLocation, functions, visible, loggingOn);
		if(comp)
			comp->isCoSim = FMIFalse;
	}else{
		return NULL;
	}
	return comp;
}

DYMOLA_STATIC void fmiFreeInstance_(FMIComponent c)
{
    fmiFreeModelInstance_(c);
}

DYMOLA_STATIC FMIStatus fmiSetupExperiment_(FMIComponent c,
											FMIBoolean relativeToleranceDefined,
											FMIReal relativeTolerance,
											FMIReal tStart,
											FMIBoolean tStopDefined,
											FMIReal tStop)
{
	/* TODO fix warning of unsuported features for CS/ME now instead of at initialization*/
	static FMIString label = "fmi2SetupExperiment";
	Component* comp = (Component*) c;
	comp->tStart = tStart;
	comp->StopTimeDefined = tStopDefined;
	comp->tStop = tStop;
	if(relativeToleranceDefined && !comp->isCoSim ){
		util_logger(comp, comp->instanceName, FMIWarning, "", "%s: tolerance control not supported for fmuType fmi2ModelExchange, setting toleranceDefined to fmi2False",label);
		comp->relativeToleranceDefined = FMIFalse;
		comp->relativeTolerance =0;
	}else{
		comp->relativeToleranceDefined = relativeToleranceDefined;
		comp->relativeTolerance = relativeTolerance;
	}
	comp->time = tStart;
	comp->icall = iDemandStart;
	util_logger(comp, comp->instanceName, FMIOK, "", "%s: startTime is set to %g",label, tStart);
	return FMIOK;
}
DYMOLA_STATIC FMIStatus fmiEnterInitializationMode_(FMIComponent c)
{
	Component* comp = (Component*) c;
	if(comp->isCoSim){
		return fmiEnterSlaveInitializationMode_(comp, comp->relativeTolerance, comp->tStart, comp->StopTimeDefined, comp->tStop);
	}else if(!comp->isCoSim){
		return fmiEnterModelInitializationMode_(comp, FMIFalse, 0);
	}
	return util_error(comp);
}
DYMOLA_STATIC FMIStatus fmiExitInitializationMode_(FMIComponent c)
{
	Component* comp = (Component*) c;
	if(comp->isCoSim){
		return fmiExitSlaveInitializationMode_(comp);
	}else if(!comp->isCoSim){
		return fmiExitModelInitializationMode_(comp);
	}
	return util_error(comp);
}

DYMOLA_STATIC FMIStatus fmiTerminate_(FMIComponent c)
{
	Component* comp = (Component*) c;
	if(comp->isCoSim){
		return fmiTerminateSlave_(comp);
	}else if(!comp->isCoSim){
		return fmiTerminateModel_(comp);
	}
	return util_error(comp);
}

DYMOLA_STATIC FMIStatus fmiReset_(FMIComponent c)
{
	return fmiResetSlave_(c);
}

#endif /* FMI_2 */

/* ----------------- local function definitions ----------------- */

static int getLargestIdemand(const FMIValueReference vr[], size_t nvr)
{
	int idemand = iDemandStart;                       
	size_t i;                                          
                                                       
	/* find biggest idemand among requested values */  
	for (i = 0; i < nvr; i++) {
		const FMIValueReference r = vr[i];
		int id = FMI_IDEMAND(r);
		if (id > idemand) {
			idemand = id;
		}
	}
	return idemand;
}
