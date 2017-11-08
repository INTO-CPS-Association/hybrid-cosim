package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

class FmuGenerator {
	def static String genFmuCppFile(String adapClassName)
	{
		'''
		#include <stdio.h>
		#include "fmi2Functions.h"
		#include <string>
		
		#include "«adapClassName».h"
		
		#include "uri.h"
		
		using namespace std;
		
		const fmi2CallbackFunctions *g_functions;
		std::string* name;
		
		shared_ptr<adaptation::«adapClassName»> g_adaptation;
		
		template<class T>
		static void log(const fmi2CallbackFunctions *functions, fmi2ComponentEnvironment componentEnvironment,
				fmi2String instanceName, fmi2Status status, fmi2String category, fmi2String message, T arg)
		{
			if (functions != NULL && functions->logger != NULL)
			{
				functions->logger(componentEnvironment, instanceName, status, category, message, arg);
			}
		}
		
		static void notimplemented(fmi2Component c, fmi2String message)
		{
			std::string base("Not implemented: %s");
			std::string m(message);
			if (g_functions != NULL)
			{
				log(g_functions, g_adaptation->getComponent(), "", fmi2Error, "error", (base + m).c_str(), "");
			}
		}
		
		template<class T>
		static void fmiprintf(fmi2String message, T arg)
		{
			if (g_functions != NULL)
			{
				log(g_functions, g_adaptation->getComponent(), name->c_str(), fmi2OK, "logAll", message, arg);
			}
		}
		
		// ---------------------------------------------------------------------------
		// FMI functions
		// ---------------------------------------------------------------------------
		extern "C" fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type fmuType, fmi2String fmuGUID,
				fmi2String fmuResourceLocation, const fmi2CallbackFunctions *functions, fmi2Boolean visible,
				fmi2Boolean loggingOn)
		{
			name = new std::string(instanceName);
			g_functions = functions;
			fmiprintf("instantiating %s\n", instanceName);
			auto resourceLoc = make_shared<std::string>(URIToNativePath(fmuResourceLocation));
			auto name  = make_shared<std::string>(instanceName);
			g_adaptation = make_shared<adaptation::«adapClassName»>(name, resourceLoc, functions);
			try
			{
				g_adaptation->initialize();
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return NULL;
			}
		
			if (g_adaptation->getLastErrorState() != fmi2OK)
				return NULL;
		
			return g_adaptation->getComponent();
		}
		
		extern "C" fmi2Status fmi2SetupExperiment(fmi2Component c, fmi2Boolean toleranceDefined, fmi2Real tolerance,
				fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime)
		{
		
			try
			{
				return g_adaptation->fmi2SetupExperiment(toleranceDefined, tolerance, startTime, stopTimeDefined, stopTime);
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2EnterInitializationMode(fmi2Component c)
		{
			try
			{
				return g_adaptation->fmi2EnterInitializationMode();
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2ExitInitializationMode(fmi2Component c)
		{
			try
			{
				return g_adaptation->fmi2ExitInitializationMode();
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2Terminate(fmi2Component c)
		{
			try
			{
				return g_adaptation->fmi2Terminate();
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2Reset(fmi2Component c)
		{
			return fmi2OK;
		}
		
		extern "C" void fmi2FreeInstance(fmi2Component c)
		{
		
		}
		
		// ---------------------------------------------------------------------------
		// FMI functions: class methods not depending of a specific model instance
		// ---------------------------------------------------------------------------
		
		extern "C" const char* fmi2GetVersion()
		{
			return fmi2Version;
		}
		
		extern "C" const char* fmi2GetTypesPlatform()
		{
			return fmi2TypesPlatform;
		}
		
		// ---------------------------------------------------------------------------
		// FMI functions: logging control, setters and getters for Real, Integer,
		// Boolean, String
		// ---------------------------------------------------------------------------
		
		extern "C" fmi2Status fmi2SetDebugLogging(fmi2Component c, fmi2Boolean loggingOn, size_t nCategories,
				const fmi2String categories[])
		{
			return fmi2OK;
		}
		
		template<class T>
		fmi2Status getX(const fmi2ValueReference vr[], size_t nvr, T value[],
				T (adaptation::«adapClassName»::*getter)(fmi2ValueReference vr))
		{
			try
			{
				fmi2Status status = g_adaptation->executeOutRules();
				if (status != fmi2OK)
					return status;
		
				status = g_adaptation->flushAllEnabledOutRules();
				if (status != fmi2OK)
					return status;
		
				for (int i = 0; i < nvr; i++)
				{
					value[i] = ((*g_adaptation).*getter)(vr[i]);
		
					status = g_adaptation->getLastErrorState();
					if (status != fmi2OK)
						return status;
				}
		
				return fmi2OK;
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2GetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
		{
			return getX(vr, nvr, value, &adaptation::«adapClassName»::getFmiValueReal);
		}
		
		extern "C" fmi2Status fmi2GetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Integer value[])
		{
			return getX(vr, nvr, value, &adaptation::«adapClassName»::getFmiValueInteger);
		}
		
		extern "C" fmi2Status fmi2GetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[])
		{
			typedef bool (adaptation::«adapClassName»::*GB)(fmi2ValueReference);
			typedef int (adaptation::«adapClassName»::*GI)(fmi2ValueReference);
		
			GB g = &adaptation::«adapClassName»::getFmiValueBoolean;
			GI i = reinterpret_cast<GI>(g);
		
			return getX(vr, nvr, value, i);
		}
		
		extern "C" fmi2Status fmi2GetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2String value[])
		{
			return fmi2Discard;
		}
		
		template<class T>
		fmi2Status setX(const fmi2ValueReference vr[], size_t nvr, T value[])
		{
			try
			{
				fmi2Status status = fmi2OK;
				for (int i = 0; i < nvr; i++)
				{
					g_adaptation->setFmiValue(vr[i], value[i]);
		
					status = g_adaptation->getLastErrorState();
					if (status != fmi2OK)
						return status;
				}
				status = g_adaptation->executeInRules();
				return status;
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2SetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[])
		{
			return setX(vr, nvr, value);
		}
		
		extern "C" fmi2Status fmi2SetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
				const fmi2Integer value[])
		{
			return setX(vr, nvr, value);
		}
		
		extern "C" fmi2Status fmi2SetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
				const fmi2Boolean value[])
		{
			return setX(vr, nvr, value);
		}
		
		extern "C" fmi2Status fmi2SetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
				const fmi2String value[])
		{
			return fmi2Discard;
		}
		
		extern "C" fmi2Status fmi2GetFMUstate(fmi2Component c, fmi2FMUstate* FMUstate)
		{
		 return g_adaptation->fmi2GetFMUstate(c,FMUstate);
		}
		extern "C" fmi2Status fmi2SetFMUstate(fmi2Component c, fmi2FMUstate FMUstate)
		{
		 return g_adaptation->fmi2SetFMUstate(c,FMUstate);
		}
		extern "C" fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* FMUstate)
		{
		 return g_adaptation->fmi2FreeFMUstate(c,FMUstate);
		}
		
		extern "C" fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate FMUstate, size_t *size)
		{
			notimplemented(c, "fmi2SerializedFMUstateSize");
			return fmi2Error;
		}
		extern "C" fmi2Status fmi2SerializeFMUstate(fmi2Component c, fmi2FMUstate FMUstate, fmi2Byte serializedState[],
				size_t size)
		{
			notimplemented(c, "fmi2SerializeFMUstate");
			return fmi2Error;
		}
		extern "C" fmi2Status fmi2DeSerializeFMUstate(fmi2Component c, const fmi2Byte serializedState[], size_t size,
				fmi2FMUstate* FMUstate)
		{
			notimplemented(c, "fmi2DeSerializeFMUstate");
			return fmi2Error;
		}
		
		extern "C" fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference vUnknown_ref[],
				size_t nUnknown, const fmi2ValueReference vKnown_ref[], size_t nKnown, const fmi2Real dvKnown[],
				fmi2Real dvUnknown[])
		{
			notimplemented(c, "fmi2GetDirectionalDerivative");
			return fmi2Error;
		}
		
		// ---------------------------------------------------------------------------
		// Functions for FMI for Co-Simulation
		// ---------------------------------------------------------------------------
		#ifdef FMI_COSIMULATION
		/* Simulating the slave */
		extern "C" fmi2Status fmi2SetRealInputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
				const fmi2Integer order[], const fmi2Real value[])
		{
			notimplemented(c, "fmi2SetRealInputDerivatives");
			return fmi2Error;
		}
		
		extern "C" fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
				const fmi2Integer order[], fmi2Real value[])
		{
			notimplemented(c, "fmi2GetRealOutputDerivatives");
			return fmi2Error;
		}
		
		extern "C" fmi2Status fmi2CancelStep(fmi2Component c)
		{
			notimplemented(c, "fmi2CancelStep");
			return fmi2Error;
		}
		
		extern "C" fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint, fmi2Real communicationStepSize,
				fmi2Boolean noSetFMUStatePriorToCurrentPoint)
		{
			try
			{
				g_adaptation->executeControlFlow(currentCommunicationPoint, communicationStepSize);
				return fmi2OK;
			} catch (adaptation::SemanticAdaptationFmiException& e)
			{
				return e.status;
			}
		}
		
		extern "C" fmi2Status fmi2GetStatus(fmi2Component c, const fmi2StatusKind s, fmi2Status *value)
		{
			return fmi2OK;
		}
		
		extern "C" fmi2Status fmi2GetRealStatus(fmi2Component c, const fmi2StatusKind s, fmi2Real *value)
		{
			return fmi2OK;
		}
		
		extern "C" fmi2Status fmi2GetIntegerStatus(fmi2Component c, const fmi2StatusKind s, fmi2Integer *value)
		{
			return fmi2OK;
		}
		
		extern "C" fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean *value)
		{
			return fmi2OK;
		}
		
		extern "C" fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String *value)
		{
			return fmi2OK;
		}
		
		/* INTO cps specific*/
		/*extern "C" fmi2Status fmi2GetMaxStepsize(fmi2Component c, fmi2Real* size)
		 {
		 return fmi2OK;
		 }*/
		
		// ---------------------------------------------------------------------------
		// Functions for FMI2 for Model Exchange
		// ---------------------------------------------------------------------------
		#else
		/* Enter and exit the different modes */
		fmi2Status fmi2EnterEventMode(fmi2Component c)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2NewDiscreteStates(fmi2Component c, fmi2EventInfo *eventInfo)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2EnterContinuousTimeMode(fmi2Component c)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2CompletedIntegratorStep(fmi2Component c, fmi2Boolean noSetFMUStatePriorToCurrentPoint,
				fmi2Boolean *enterEventMode, fmi2Boolean *terminateSimulation)
		{
			return fmi2Error;
		}
		
		/* Providing independent variables and re-initialization of caching */
		fmi2Status fmi2SetTime(fmi2Component c, fmi2Real time)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2SetContinuousStates(fmi2Component c, const fmi2Real x[], size_t nx)
		{
			return fmi2Error;
		}
		
		/* Evaluation of the model equations */
		fmi2Status fmi2GetDerivatives(fmi2Component c, fmi2Real derivatives[], size_t nx)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2GetEventIndicators(fmi2Component c, fmi2Real eventIndicators[], size_t ni)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2GetContinuousStates(fmi2Component c, fmi2Real states[], size_t nx)
		{
			return fmi2Error;
		}
		
		fmi2Status fmi2GetNominalsOfContinuousStates(fmi2Component c, fmi2Real x_nominal[], size_t nx)
		{
			return fmi2Error;
		}
		#endif // Model Exchange
		'''
	}
}