#ifndef fmi2Import_h
#define fmi2Import_h
/* 
 *	Declare data structure used for import of FMUs in Modelica.
 
*/


/* For other platforms than those covered below, static linking of FMU binaries are expected to be used */
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)

#include "windows.h"

#else

typedef void* HINSTANCE;


#if defined(__linux__) && !defined(NO_FILE)
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
/* might need access to non-standard function dladdr */
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU

typedef void* HMODULE;


/* Linux shared object implementations of Windows specific DLL handling functions */
static void* LoadLibrary(const char* lpFileName)
{
	char* pathFMU;
	char* soDirs = NULL;
	char* dir;
	void* handle = NULL;

	/* Search the binary directories for the FMU. */
	/* Cannot rely on the internal search in dlopen since it uses LD_LIBRARY_PATH
	   value set when process starts, which is too early. */
	pathFMU = getenv("LD_LIBRARY_PATH_FMU");
	if (pathFMU == NULL) {
		ModelicaError("Failed to get environment variable LD_LIBRARY_PATH_FMU");
		goto done;
	}

	soDirs = strdup(pathFMU);
	dir = strtok(soDirs, ":");
	while (dir != NULL) {
		char soPath[1024];
		struct stat sb;

		if (snprintf(soPath, sizeof(soPath), "%s/%s", dir, lpFileName) == sizeof(soPath)) {
			ModelicaFormatError("Internal buffer too small when loading %s", lpFileName);
		}
		if (stat(soPath, &sb) == 0) {	
			handle = dlopen(soPath, RTLD_NOW);
			if (handle != NULL) {
				goto done;
			}
			ModelicaError(dlerror());
		}
		dir = strtok(NULL, ":");
	}
	ModelicaFormatError("Did not find %s in the paths in LD_LIBRARY_PATH_FMU = %s", lpFileName, pathFMU);

done:
	free(soDirs);
	return handle;
}
static void* GetProcAddress(void* hModule, char* lpProcName)
{
	return dlsym(hModule, lpProcName); 
}
static void FreeLibrary(void* hModule)
{
	dlclose(hModule); 
}
#endif /* defined(__linux__) && !defined(NO_FILE) */
#endif /* defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) */

#include "fmi2Functions.h"
#include "fmi2TypesPlatform.h"
#include "fmi2FunctionTypes.h"


/*Common funcitons*/
typedef fmi2Component (*fmi2InstantiateFunc)(fmi2String, fmi2Type, fmi2String, fmi2String, const fmi2CallbackFunctions*, fmi2Boolean, fmi2Boolean);
typedef fmi2Status (*fmi2SetupExperimentFunc)         (fmi2Component, fmi2Boolean, fmi2Real, fmi2Real, fmi2Boolean, fmi2Real);
typedef fmi2Status (*fmi2EnterInitializationModeFunc) (fmi2Component);
typedef fmi2Status (*fmi2ExitInitializationModeFunc)  (fmi2Component);
typedef fmi2Status (*fmi2TerminateFunc)               (fmi2Component);
typedef void       (*fmi2FreeInstanceFunc)(fmi2Component);
typedef fmi2Status (*fmi2ResetFunc)                   (fmi2Component);
typedef fmi2Status (*fmi2GetFMUstateFunc)(fmi2Component, fmi2FMUstate*);
typedef fmi2Status (*fmi2SetFMUstateFunc)(fmi2Component, fmi2FMUstate);
typedef fmi2Status (*fmi2FreeFMUstateFunc)(fmi2Component, fmi2FMUstate*);
typedef fmi2Status (*fmi2SetRealFunc)(fmi2Component , const fmi2ValueReference[], size_t, const fmi2Real[]);
typedef fmi2Status (*fmi2GetRealFunc)(fmi2Component , const fmi2ValueReference[], size_t, fmi2Real[]);
typedef fmi2Status (*fmi2SetIntegerFunc)(fmi2Component , const fmi2ValueReference[], size_t, const fmi2Integer[]);
typedef fmi2Status (*fmi2GetIntegerFunc)(fmi2Component , const fmi2ValueReference[], size_t, fmi2Integer[]);
typedef fmi2Status (*fmi2SetBooleanFunc)(fmi2Component , const fmi2ValueReference[], size_t, const fmi2Boolean[]);
typedef fmi2Status (*fmi2GetBooleanFunc)(fmi2Component , const fmi2ValueReference[], size_t, fmi2Boolean[]);
typedef fmi2Status (*fmi2SetStringFunc)(fmi2Component , const fmi2ValueReference[], size_t, const fmi2String[]);
typedef fmi2Status (*fmi2GetStringFunc)(fmi2Component , const fmi2ValueReference[], size_t, fmi2String[]);
typedef fmi2Status (*fmi2GetDirectionalDerivativeFunc)(fmi2Component, const fmi2ValueReference[], size_t, const fmi2ValueReference[], size_t, const fmi2Real[], fmi2Real[]);


/*ME functions*/
typedef fmi2Status (*fmi2SetTimeFunc)(fmi2Component, fmi2Real);
typedef fmi2Status (*fmi2SetContinuousStatesFunc)(fmi2Component, const fmi2Real[], size_t);
typedef fmi2Status (*fmi2GetContinuousStatesFunc)(fmi2Component, fmi2Real[], size_t);
typedef fmi2Status (*fmi2GetDerivativesFunc)(fmi2Component, fmi2Real[], size_t);
typedef fmi2Status (*fmi2GetEventIndicatorsFunc)(fmi2Component, fmi2Real[], size_t);
typedef fmi2Status (*fmi2EnterEventModeFunc)(fmi2Component c);
typedef fmi2Status (*fmi2NewDiscreteStatesFunc)(fmi2Component c, fmi2EventInfo* eventInfo);
typedef fmi2Status (*fmi2EnterContinuousTimeModeFunc)(fmi2Component c );
typedef fmi2Status (*fmi2CompletedIntegratorStepFunc)(fmi2Component c, fmi2Boolean noSetFMUStatePriorToCurrentPoint, fmi2Boolean* enterEventMode, fmi2Boolean* terminateSimulation);

/* CS functions */
typedef fmi2Status (*fmi2DoStepFunc)(fmi2Component, fmi2Real, fmi2Real, fmi2Boolean);
typedef fmi2Status (*fmi2GetBooleanStatusFunc)(fmi2Component, const fmi2StatusKind, fmi2Boolean*);
typedef fmi2Status (*fmi2SetRealInputDerivativesFunc)(fmi2Component, const fmi2ValueReference[],const size_t,const fmi2Integer [],const fmi2Real []);

typedef fmi2Status (*fmi2HybridDoStepFunc)(fmi2Component, fmi2Real, fmi2Real, fmi2Boolean, fmi2Boolean*, fmi2Real*);

typedef enum {dyfmi2InstantiationMode, dyfmi2InitializationMode, dyfmi2EventMode, dyfmi2ContinuousTimeMode}dyfmi2mode;

struct dy_fmi2Extended 
{
  fmi2Component m;
  double dyTime;
  double dyLastTime;
  double dyFirstTimeEvent;
  int dyTriggered;
  dyfmi2mode currentMode;
  int discreteInputChanged;
  fmi2FMUstate dyFMUstate;
  double dyLastStepTime;
  HINSTANCE hInst;

  fmi2InstantiateFunc dyFmiInstantiate;
  fmi2FreeInstanceFunc dyFmiFreeInstance;
  fmi2SetupExperimentFunc dyFmiSetupExperiment;
  fmi2EnterInitializationModeFunc dyFmiEnterInitializationMode;
  fmi2ExitInitializationModeFunc dyFmiExitInitializationMode;
  fmi2TerminateFunc dyFmiTerminate;
  fmi2ResetFunc dyFmiReset;

  fmi2SetRealFunc dyFmiSetReal;
  fmi2GetRealFunc dyFmiGetReal;
  fmi2SetIntegerFunc dyFmiSetInteger;
  fmi2GetIntegerFunc dyFmiGetInteger;
  fmi2SetBooleanFunc dyFmiSetBoolean;
  fmi2GetBooleanFunc dyFmiGetBoolean;
  fmi2SetStringFunc dyFmiSetString;
  fmi2GetStringFunc dyFmiGetString;
  fmi2GetDirectionalDerivativeFunc dyFmiGetDirectionalDerivative;
  fmi2SetFMUstateFunc dyFmiSetFMUstate;
  fmi2GetFMUstateFunc  dyFmiGetFMUstate;
  fmi2FreeFMUstateFunc dyFmiFreeFMUstate;

  fmi2SetTimeFunc dyFmiSetTime;
  fmi2SetContinuousStatesFunc dyFmiSetContinuousStates;
  fmi2GetContinuousStatesFunc dyFmiGetContinuousStates;
  fmi2CompletedIntegratorStepFunc dyFmiCompletedIntegratorStep;
  fmi2GetDerivativesFunc dyFmiGetDerivatives;
  fmi2GetEventIndicatorsFunc dyFmiGetEventIndicators;
  fmi2EnterEventModeFunc dyFmiEnterEventMode;
  fmi2NewDiscreteStatesFunc dyFmiNewDiscreteStates;
  fmi2EnterContinuousTimeModeFunc dyFmiEnterContinuousTimeMode;
  
  fmi2DoStepFunc dyFmiDoStep;
  fmi2GetBooleanStatusFunc dyFmiGetBooleanStatus;
  fmi2SetRealInputDerivativesFunc dyFmiSetRealInputDerivatives;
  fmi2HybridDoStepFunc dyFmiHybridDoStep;
}; 

#endif
