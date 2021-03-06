/* -------------------------------------------------------------------------
 * sim_support.c
 * Functions used by both FMU simulators fmu20sim_me and fmu20sim_cs
 * to parse command-line arguments, to unzip and load an fmu,
 * to write CSV file, and more.
 *
 * Revision history
 *  07.03.2014 initial version released in FMU SDK 2.0.0
 *  10.04.2014 use FMI 2.0 headers that prefix function and type names with 'fmi2'.
 *             When 'fmi2' functions are not found in loaded DLL, look also for
 *             FMI 2.0 RC1 function names.
 *
 * Author: Adrian Tirea
 * Copyright QTronic GmbH. All rights reserved.
 * -------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <dlfcn.h>
#include "fmi2.h"
#include "sim_support.h"

#define FMI_COSIMULATION
extern FMU fmu;


//int unzip(const char *zipPath, const char *outPath) {
//    int code;
//    char cwd[BUFSIZE];
//    char binPath[BUFSIZE];
//    int n = strlen(UNZIP_CMD) + strlen(outPath) + 3 +  strlen(zipPath) + 9;
//    char* cmd = (char*)calloc(sizeof(char), n);
//
//    // remember current directory
//    if (!GetCurrentDirectory(BUFSIZE, cwd)) {
//        printf ("error: Could not get current directory\n");
//        return 0; // error
//    }
//
//    // change to %FMUSDK_HOME%\bin to find 7z.dll and 7z.exe
//    if (!GetEnvironmentVariable("FMUSDK_HOME", binPath, BUFSIZE)) {
//        if (GetLastError() == ERROR_ENVVAR_NOT_FOUND) {
//            printf ("error: Environment variable FMUSDK_HOME not defined\n");
//        }
//        else {
//            printf ("error: Could not get value of FMUSDK_HOME\n");
//        }
//        return 0; // error
//    }
//    strcat(binPath, "\\bin");
//    if (!SetCurrentDirectory(binPath)) {
//        printf ("error: could not change to directory '%s'\n", binPath);
//        return 0; // error
//    }
//
//    // run the unzip command
//    // remove "> NUL" to see the unzip protocol
//    sprintf(cmd, "%s\"%s\" \"%s\" > NUL", UNZIP_CMD, outPath, zipPath);
//    // printf("cmd='%s'\n", cmd);
//    code = system(cmd);
//    free(cmd);
//    if (code != SEVEN_ZIP_NO_ERROR) {
//        printf("7z: ");
//        switch (code) {
//            case SEVEN_ZIP_WARNING:            printf("warning\n"); break;
//            case SEVEN_ZIP_ERROR:              printf("error\n"); break;
//            case SEVEN_ZIP_COMMAND_LINE_ERROR: printf("command line error\n"); break;
//            case SEVEN_ZIP_OUT_OF_MEMORY:      printf("out of memory\n"); break;
//            case SEVEN_ZIP_STOPPED_BY_USER:    printf("stopped by user\n"); break;
//            default: printf("unknown problem\n");
//        }
//    }
//
//    // restore current directory
//    SetCurrentDirectory(cwd);
//    return (code == SEVEN_ZIP_NO_ERROR || code == SEVEN_ZIP_WARNING) ? 1 : 0;
//}
//
//// fileName is an absolute path, e.g. C:\test\a.fmu
//// or relative to the current dir, e.g. ..\test\a.fmu
//// Does not check for existence of the file
//static char* getFmuPath(const char* fileName){
//    char pathName[MAX_PATH];
//    int n = GetFullPathName(fileName, MAX_PATH, pathName, NULL);
//    return n ? strdup(pathName) : NULL;
//}
//
//static char* getTmpPath() {
//    char tmpPath[BUFSIZE];
//    if(! GetTempPath(BUFSIZE, tmpPath)) {
//        printf ("error: Could not find temporary disk space\n");
//        return NULL;
//    }
//    strcat(tmpPath, "fmu\\");
//    return strdup(tmpPath);
//}
//
//char *getTempResourcesLocation() {
//    char *tempPath = getTmpPath();
//    char *resourcesLocation = (char *)calloc(sizeof(char), 9 + strlen(RESOURCES_DIR) + strlen(tempPath));
//    strcpy(resourcesLocation, "file:///");
//    strcat(resourcesLocation, tempPath);
//    strcat(resourcesLocation, RESOURCES_DIR);
//    free(tempPath);
//    return resourcesLocation;
//}

static void *getAdr(int *success, void *dllHandle, const char *functionName, const char* preamble) {

    int length = strlen(preamble) + strlen(functionName) + 1;
    char* new_name = malloc(length);  // allocate memory
    strcpy(new_name, preamble);  // copy first string
    strcat(new_name, functionName);
    void* fp = dlsym(dllHandle, new_name);
    if (!fp) {
        printf("warning: Function %s not found in dll\n", new_name);
        *success = 0;
    }
    free(new_name);
    return fp;
}

// Load the given dll and set function pointers in fmu
// Return 0 to indicate failure
int loadDll(const char* dllPath, FMU *fmu, const char* preamble) {
    int x = 1, s = 1;
    //HMODULE h = LoadLibrary(dllPath);
    void *h = dlopen(dllPath, RTLD_LAZY);
    printf("%s", dlerror());
    if (!h) {
        printf("error: Could not load %s\n", dllPath);
        return 0; // failure
    }
    fmu->dllHandle = h;
    fmu->getTypesPlatform          = (fmi2GetTypesPlatformTYPE *)      getAdr(&s, h, "fmi2GetTypesPlatform", preamble);
    fmu->getVersion                = (fmi2GetVersionTYPE *)            getAdr(&s, h, "fmi2GetVersion", preamble);
    fmu->setDebugLogging           = (fmi2SetDebugLoggingTYPE *)       getAdr(&s, h, "fmi2SetDebugLogging",preamble);
    fmu->instantiate               = (fmi2InstantiateTYPE *)           getAdr(&s, h, "fmi2Instantiate", preamble);
    fmu->freeInstance              = (fmi2FreeInstanceTYPE *)          getAdr(&s, h, "fmi2FreeInstance", preamble);
    fmu->setupExperiment           = (fmi2SetupExperimentTYPE *)       getAdr(&s, h, "fmi2SetupExperiment", preamble);
    fmu->enterInitializationMode   = (fmi2EnterInitializationModeTYPE *) getAdr(&s, h, "fmi2EnterInitializationMode", preamble);
    fmu->exitInitializationMode    = (fmi2ExitInitializationModeTYPE *) getAdr(&s, h, "fmi2ExitInitializationMode", preamble);
    fmu->terminate                 = (fmi2TerminateTYPE *)             getAdr(&s, h, "fmi2Terminate", preamble);
    fmu->reset                     = (fmi2ResetTYPE *)                 getAdr(&s, h, "fmi2Reset", preamble);
    fmu->getReal                   = (fmi2GetRealTYPE *)               getAdr(&s, h, "fmi2GetReal", preamble);
    fmu->getInteger                = (fmi2GetIntegerTYPE *)            getAdr(&s, h, "fmi2GetInteger", preamble);
    fmu->getBoolean                = (fmi2GetBooleanTYPE *)            getAdr(&s, h, "fmi2GetBoolean", preamble);
    fmu->getString                 = (fmi2GetStringTYPE *)             getAdr(&s, h, "fmi2GetString", preamble);
    fmu->setReal                   = (fmi2SetRealTYPE *)               getAdr(&s, h, "fmi2SetReal", preamble);
    fmu->setInteger                = (fmi2SetIntegerTYPE *)            getAdr(&s, h, "fmi2SetInteger", preamble);
    fmu->setBoolean                = (fmi2SetBooleanTYPE *)            getAdr(&s, h, "fmi2SetBoolean", preamble);
    fmu->setString                 = (fmi2SetStringTYPE *)             getAdr(&s, h, "fmi2SetString", preamble);
    fmu->getFMUstate               = (fmi2GetFMUstateTYPE *)           getAdr(&s, h, "fmi2GetFMUstate", preamble);
    fmu->setFMUstate               = (fmi2SetFMUstateTYPE *)           getAdr(&s, h, "fmi2SetFMUstate", preamble);
    fmu->freeFMUstate              = (fmi2FreeFMUstateTYPE *)          getAdr(&s, h, "fmi2FreeFMUstate", preamble);
    fmu->serializedFMUstateSize    = (fmi2SerializedFMUstateSizeTYPE *) getAdr(&s, h, "fmi2SerializedFMUstateSize", preamble);
    fmu->serializeFMUstate         = (fmi2SerializeFMUstateTYPE *)     getAdr(&s, h, "fmi2SerializeFMUstate", preamble);
    fmu->deSerializeFMUstate       = (fmi2DeSerializeFMUstateTYPE *)   getAdr(&s, h, "fmi2DeSerializeFMUstate", preamble);
    fmu->getDirectionalDerivative  = (fmi2GetDirectionalDerivativeTYPE *) getAdr(&s, h, "fmi2GetDirectionalDerivative", preamble);
#ifdef FMI_COSIMULATION
    fmu->setRealInputDerivatives   = (fmi2SetRealInputDerivativesTYPE *) getAdr(&s, h, "fmi2SetRealInputDerivatives", preamble);
    fmu->getRealOutputDerivatives  = (fmi2GetRealOutputDerivativesTYPE *) getAdr(&s, h, "fmi2GetRealOutputDerivatives", preamble);
    fmu->doStep                    = (fmi2DoStepTYPE *)                getAdr(&s, h, "fmi2DoStep", preamble);
    fmu->cancelStep                = (fmi2CancelStepTYPE *)            getAdr(&s, h, "fmi2CancelStep", preamble);
    fmu->getStatus                 = (fmi2GetStatusTYPE *)             getAdr(&s, h, "fmi2GetStatus", preamble);
    fmu->getRealStatus             = (fmi2GetRealStatusTYPE *)         getAdr(&s, h, "fmi2GetRealStatus", preamble);
    fmu->getIntegerStatus          = (fmi2GetIntegerStatusTYPE *)      getAdr(&s, h, "fmi2GetIntegerStatus", preamble);
    fmu->getBooleanStatus          = (fmi2GetBooleanStatusTYPE *)      getAdr(&s, h, "fmi2GetBooleanStatus", preamble);
    fmu->getStringStatus           = (fmi2GetStringStatusTYPE *)       getAdr(&s, h, "fmi2GetStringStatus", preamble);
#else // FMI2 for Model Exchange
    fmu->enterEventMode            = (fmi2EnterEventModeTYPE *)        getAdr(&s, h, "fmi2EnterEventMode", preamble);
    fmu->newDiscreteStates         = (fmi2NewDiscreteStatesTYPE *)     getAdr(&s, h, "fmi2NewDiscreteStates", preamble);
    fmu->enterContinuousTimeMode   = (fmi2EnterContinuousTimeModeTYPE *) getAdr(&s, h, "fmi2EnterContinuousTimeMode", preamble);
    fmu->completedIntegratorStep   = (fmi2CompletedIntegratorStepTYPE *) getAdr(&s, h, "fmi2CompletedIntegratorStep", preamble);
    fmu->setTime                   = (fmi2SetTimeTYPE *)               getAdr(&s, h, "fmi2SetTime", preamble);
    fmu->setContinuousStates       = (fmi2SetContinuousStatesTYPE *)   getAdr(&s, h, "fmi2SetContinuousStates", preamble);
    fmu->getDerivatives            = (fmi2GetDerivativesTYPE *)        getAdr(&s, h, "fmi2GetDerivatives", preamble);
    fmu->getEventIndicators        = (fmi2GetEventIndicatorsTYPE *)    getAdr(&s, h, "fmi2GetEventIndicators", preamble);
    fmu->getContinuousStates       = (fmi2GetContinuousStatesTYPE *)   getAdr(&s, h, "fmi2GetContinuousStates", preamble);
    fmu->getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *) getAdr(&s, h, "fmi2GetNominalsOfContinuousStates", preamble);
#endif

    if (fmu->getVersion == NULL && fmu->instantiate == NULL) {
        printf("warning: Functions from FMI 2.0 could not be found in %s\n", dllPath);
        printf("warning: Simulator will look for FMI 2.0 RC1 functions names...\n");
        fmu->getTypesPlatform          = (fmi2GetTypesPlatformTYPE *)      getAdr(&s, h, "fmiGetTypesPlatform", preamble);
        fmu->getVersion                = (fmi2GetVersionTYPE *)            getAdr(&s, h, "fmiGetVersion", preamble);
        fmu->setDebugLogging           = (fmi2SetDebugLoggingTYPE *)       getAdr(&s, h, "fmiSetDebugLogging", preamble);
        fmu->instantiate               = (fmi2InstantiateTYPE *)           getAdr(&s, h, "fmiInstantiate", preamble);
        fmu->freeInstance              = (fmi2FreeInstanceTYPE *)          getAdr(&s, h, "fmiFreeInstance", preamble);
        fmu->setupExperiment           = (fmi2SetupExperimentTYPE *)       getAdr(&s, h, "fmiSetupExperiment", preamble);
        fmu->enterInitializationMode   = (fmi2EnterInitializationModeTYPE *) getAdr(&s, h, "fmiEnterInitializationMode", preamble);
        fmu->exitInitializationMode    = (fmi2ExitInitializationModeTYPE *) getAdr(&s, h, "fmiExitInitializationMode", preamble);
        fmu->terminate                 = (fmi2TerminateTYPE *)             getAdr(&s, h, "fmiTerminate", preamble);
        fmu->reset                     = (fmi2ResetTYPE *)                 getAdr(&s, h, "fmiReset", preamble);
        fmu->getReal                   = (fmi2GetRealTYPE *)               getAdr(&s, h, "fmiGetReal", preamble);
        fmu->getInteger                = (fmi2GetIntegerTYPE *)            getAdr(&s, h, "fmiGetInteger", preamble);
        fmu->getBoolean                = (fmi2GetBooleanTYPE *)            getAdr(&s, h, "fmiGetBoolean", preamble);
        fmu->getString                 = (fmi2GetStringTYPE *)             getAdr(&s, h, "fmiGetString", preamble);
        fmu->setReal                   = (fmi2SetRealTYPE *)               getAdr(&s, h, "fmiSetReal", preamble);
        fmu->setInteger                = (fmi2SetIntegerTYPE *)            getAdr(&s, h, "fmiSetInteger", preamble);
        fmu->setBoolean                = (fmi2SetBooleanTYPE *)            getAdr(&s, h, "fmiSetBoolean", preamble);
        fmu->setString                 = (fmi2SetStringTYPE *)             getAdr(&s, h, "fmiSetString", preamble);
        fmu->getFMUstate               = (fmi2GetFMUstateTYPE *)           getAdr(&s, h, "fmiGetFMUstate", preamble);
        fmu->setFMUstate               = (fmi2SetFMUstateTYPE *)           getAdr(&s, h, "fmiSetFMUstate", preamble);
        fmu->freeFMUstate              = (fmi2FreeFMUstateTYPE *)          getAdr(&s, h, "fmiFreeFMUstate", preamble);
        fmu->serializedFMUstateSize    = (fmi2SerializedFMUstateSizeTYPE *) getAdr(&s, h, "fmiSerializedFMUstateSize", preamble);
        fmu->serializeFMUstate         = (fmi2SerializeFMUstateTYPE *)     getAdr(&s, h, "fmiSerializeFMUstate", preamble);
        fmu->deSerializeFMUstate       = (fmi2DeSerializeFMUstateTYPE *)   getAdr(&s, h, "fmiDeSerializeFMUstate", preamble);
        fmu->getDirectionalDerivative  = (fmi2GetDirectionalDerivativeTYPE *) getAdr(&s, h, "fmiGetDirectionalDerivative", preamble);
    #ifdef FMI_COSIMULATION
        fmu->setRealInputDerivatives   = (fmi2SetRealInputDerivativesTYPE *) getAdr(&s, h, "fmiSetRealInputDerivatives", preamble);
        fmu->getRealOutputDerivatives  = (fmi2GetRealOutputDerivativesTYPE *) getAdr(&s, h, "fmiGetRealOutputDerivatives", preamble);
        fmu->doStep                    = (fmi2DoStepTYPE *)                getAdr(&s, h, "fmiDoStep", preamble);
        fmu->cancelStep                = (fmi2CancelStepTYPE *)            getAdr(&s, h, "fmiCancelStep", preamble);
        fmu->getStatus                 = (fmi2GetStatusTYPE *)             getAdr(&s, h, "fmiGetStatus", preamble);
        fmu->getRealStatus             = (fmi2GetRealStatusTYPE *)         getAdr(&s, h, "fmiGetRealStatus", preamble);
        fmu->getIntegerStatus          = (fmi2GetIntegerStatusTYPE *)      getAdr(&s, h, "fmiGetIntegerStatus", preamble);
        fmu->getBooleanStatus          = (fmi2GetBooleanStatusTYPE *)      getAdr(&s, h, "fmiGetBooleanStatus", preamble);
        fmu->getStringStatus           = (fmi2GetStringStatusTYPE *)       getAdr(&s, h, "fmiGetStringStatus", preamble);
    #else // FMI2 for Model Exchange
        fmu->enterEventMode            = (fmi2EnterEventModeTYPE *)        getAdr(&s, h, "fmiEnterEventMode", preamble);
        fmu->newDiscreteStates         = (fmi2NewDiscreteStatesTYPE *)     getAdr(&s, h, "fmiNewDiscreteStates", preamble);
        fmu->enterContinuousTimeMode   = (fmi2EnterContinuousTimeModeTYPE *) getAdr(&s, h, "fmiEnterContinuousTimeMode", preamble);
        fmu->completedIntegratorStep   = (fmi2CompletedIntegratorStepTYPE *) getAdr(&s, h, "fmiCompletedIntegratorStep", preamble);
        fmu->setTime                   = (fmi2SetTimeTYPE *)               getAdr(&s, h, "fmiSetTime", preamble);
        fmu->setContinuousStates       = (fmi2SetContinuousStatesTYPE *)   getAdr(&s, h, "fmiSetContinuousStates", preamble);
        fmu->getDerivatives            = (fmi2GetDerivativesTYPE *)        getAdr(&s, h, "fmiGetDerivatives", preamble);
        fmu->getEventIndicators        = (fmi2GetEventIndicatorsTYPE *)    getAdr(&s, h, "fmiGetEventIndicators", preamble);
        fmu->getContinuousStates       = (fmi2GetContinuousStatesTYPE *)   getAdr(&s, h, "fmiGetContinuousStates", preamble);
        fmu->getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *) getAdr(&s, h, "fmiGetNominalsOfContinuousStates", preamble);
    #endif
    }
    return s;
}

//static void printModelDescription(ModelDescription* md){
//    Element* e = (Element*)md;
//    int i;
//    int n; // number of attributes
//    const char **attributes = getAttributesAsArray(e, &n);
//    Component *component;
//
//    if (!attributes) {
//        printf("ModelDescription printing aborted.");
//        return;
//    }
//    printf("%s\n", getElementTypeName(e));
//    for (i = 0; i < n; i += 2) {
//        printf("  %s=%s\n", attributes[i], attributes[i+1]);
//    }
//    free((void *)attributes);
//
//#ifdef FMI_COSIMULATION
//    component = getCoSimulation(md);
//    if (!component) {
//        printf("error: No CoSimulation element found in model description. This FMU is not for Co-Simulation.\n");
//        exit(EXIT_FAILURE);
//    }
//#else // FMI_MODEL_EXCHANGE
//    component = getModelExchange(md);
//    if (!component) {
//        printf("error: No ModelExchange element found in model description. This FMU is not for Model Exchange.\n");
//        exit(EXIT_FAILURE);
//    }
//#endif
//    printf("%s\n", getElementTypeName((Element *)component));
//    attributes = getAttributesAsArray((Element *)component, &n);
//    if (!attributes) {
//        printf("ModelDescription printing aborted.");
//        return;
//    }
//    for (i = 0; i < n; i += 2) {
//        printf("  %s=%s\n", attributes[i], attributes[i+1]);
//    }
//
//    free((void *)attributes);
//}
//
//void loadFMU(const char* fmuFileName) {
//    char* fmuPath;
//    char* tmpPath;
//    char* xmlPath;
//    char* dllPath;
//    const char *modelId;
//
//    // get absolute path to FMU, NULL if not found
//    fmuPath = getFmuPath(fmuFileName);
//    if (!fmuPath) exit(EXIT_FAILURE);
//
//    // unzip the FMU to the tmpPath directory
//    tmpPath = getTmpPath();
//    if (!unzip(fmuPath, tmpPath)) exit(EXIT_FAILURE);
//
//    // parse tmpPath\modelDescription.xml
//    xmlPath = calloc(sizeof(char), strlen(tmpPath) + strlen(XML_FILE) + 1);
//    sprintf(xmlPath, "%s%s", tmpPath, XML_FILE);
//    fmu.modelDescription = parse(xmlPath);
//    free(xmlPath);
//    if (!fmu.modelDescription) exit(EXIT_FAILURE);
//    printModelDescription(fmu.modelDescription);
//#ifdef FMI_COSIMULATION
//    modelId = getAttributeValue((Element *)getCoSimulation(fmu.modelDescription), att_modelIdentifier);
//#else // FMI_MODEL_EXCHANGE
//    modelId = getAttributeValue((Element *)getModelExchange(fmu.modelDescription), att_modelIdentifier);
//#endif
//    // load the FMU dll
//    dllPath = calloc(sizeof(char), strlen(tmpPath) + strlen(DLL_DIR)
//        + strlen(modelId) +  strlen(".dll") + 1);
//    sprintf(dllPath, "%s%s%s.dll", tmpPath, DLL_DIR, modelId);
//    if (!loadDll(dllPath, &fmu)) {
//        exit(EXIT_FAILURE);
//    }
//    free(dllPath);
//    free(fmuPath);
//    free(tmpPath);
//}
//
//void deleteUnzippedFiles() {
//    const char *fmuTempPath = getTmpPath();
//    char *cmd = (char *)calloc(15 + strlen(fmuTempPath), sizeof(char));
//    sprintf(cmd, "rmdir /S /Q %s", fmuTempPath);
//    system(cmd);
//    free(cmd);
//}
//
//static void doubleToCommaString(char* buffer, double r){
//    char* comma;
//    sprintf(buffer, "%.16g", r);
//    comma = strchr(buffer, '.');
//    if (comma) *comma = ',';
//}
//
//// output time and all variables in CSV format
//// if separator is ',', columns are separated by ',' and '.' is used for floating-point numbers.
//// otherwise, the given separator (e.g. ';' or '\t') is to separate columns, and ',' is used
//// as decimal dot in floating-point numbers.
//void outputRow(FMU *fmu, fmi2Component c, double time, FILE* file, char separator, fmi2Boolean header) {
//    int k;
//    fmi2Real r;
//    fmi2Integer i;
//    fmi2Boolean b;
//    fmi2String s;
//    fmi2ValueReference vr;
//    int n = getScalarVariableSize(fmu->modelDescription);
//    char buffer[32];
//
//    // print first column
//    if (header) {
//        fprintf(file, "time");
//    } else {
//        if (separator==',')
//            fprintf(file, "%.16g", time);
//        else {
//            // separator is e.g. ';' or '\t'
//            doubleToCommaString(buffer, time);
//            fprintf(file, "%s", buffer);
//        }
//    }
//
//    // print all other columns
//    for (k = 0; k < n; k++) {
//        ScalarVariable *sv = getScalarVariable(fmu->modelDescription, k);
//        if (header) {
//            // output names only
//            if (separator == ',') {
//                // treat array element, e.g. print a[1, 2] as a[1.2]
//                const char *s = getAttributeValue((Element *)sv, att_name);
//                fprintf(file, "%c", separator);
//                while (*s) {
//                    if (*s != ' ') {
//                        fprintf(file, "%c", *s == ',' ? '.' : *s);
//                    }
//                    s++;
//                }
//            } else {
//                fprintf(file, "%c%s", separator, getAttributeValue((Element *)sv, att_name));
//            }
//        } else {
//            // output values
//            vr = getValueReference(sv);
//            switch (getElementType(getTypeSpec(sv))) {
//                case elm_Real:
//                    fmu->getReal(c, &vr, 1, &r);
//                    if (separator == ',') {
//                        fprintf(file, ",%.16g", r);
//                    } else {
//                        // separator is e.g. ';' or '\t'
//                        doubleToCommaString(buffer, r);
//                        fprintf(file, "%c%s", separator, buffer);
//                    }
//                    break;
//                case elm_Integer:
//                case elm_Enumeration:
//                    fmu->getInteger(c, &vr, 1, &i);
//                    fprintf(file, "%c%d", separator, i);
//                    break;
//                case elm_Boolean:
//                    fmu->getBoolean(c, &vr, 1, &b);
//                    fprintf(file, "%c%d", separator, b);
//                    break;
//                case elm_String:
//                    fmu->getString(c, &vr, 1, &s);
//                    fprintf(file, "%c%s", separator, s);
//                    break;
//                default:
//                    fprintf(file, "%cNoValueForType=%d", separator, getElementType(getTypeSpec(sv)));
//            }
//        }
//    } // for
//
//    // terminate this row
//    fprintf(file, "\n");
//}
//
static const char* fmi2StatusToString(fmi2Status status){
    switch (status){
        case fmi2OK:      return "ok";
        case fmi2Warning: return "warning";
        case fmi2Discard: return "discard";
        case fmi2Error:   return "error";
        case fmi2Fatal:   return "fatal";
    #ifdef FMI_COSIMULATION
        case fmi2Pending: return "fmi2Pending";
    #endif
        default:         return "?";
    }
}

// search a fmu for the given variable, matching the type specified.
// return NULL if not found
//static ScalarVariable* getSV(FMU* fmu, char type, fmi2ValueReference vr) {
//    return NULL;
//    int i;
//    int n = getScalarVariableSize(fmu->modelDescription);
//    Elm tp;
//
//    switch (type) {
//        case 'r': tp = elm_Real;    break;
//        case 'i': tp = elm_Integer; break;
//        case 'b': tp = elm_Boolean; break;
//        case 's': tp = elm_String;  break;
//        default : tp = elm_BAD_DEFINED;
//    }
//    for (i = 0; i < n; i++) {
//        ScalarVariable* sv = getScalarVariable(fmu->modelDescription ,i);
//        if (vr == getValueReference(sv) && tp == getElementType(getTypeSpec(sv))) {
//            return sv;
//        }
//    }
//    return NULL;
//}

// replace e.g. #r1365# by variable name and ## by # in message
// copies the result to buffer
static void replaceRefsInMessage(const char* msg, char* buffer, int nBuffer, FMU* fmu){
    int i = 0; // position in msg
    int k = 0; // position in buffer
    int n;
    char c = msg[i];
    while (c != '\0' && k < nBuffer) {
        if (c != '#') {
            buffer[k++] = c;
            i++;
            c = msg[i];
        } else {

            char* end = strchr(msg + i + 1, '#');
            if (!end) {
                printf("unmatched '#' in '%s'\n", msg);
                buffer[k++] = '#';
                break;
            }
            n = end - (msg + i);
            if (n == 1) {
                // ## detected, output #
                buffer[k++] = '#';
                i += 2;
                c = msg[i];

            } else {
                char type = msg[i + 1]; // one of ribs
                fmi2ValueReference vr;
                int nvr = sscanf(msg + i + 2, "%u", &vr);
                if (nvr == 1) {
                    // vr of type detected, e.g. #r12#
                    //ScalarVariable* sv = getSV(fmu, type, vr);
                    //const char* name = sv ? getAttributeValue((Element *)sv, att_name) : "?";
                    //sprintf(buffer + k, "%s", name);
                    //k += strlen(name);
                    //i += (n+1);
                    //c = msg[i];

                } else {
                    // could not parse the number
                    printf("illegal value reference at position %d in '%s'\n", i + 2, msg);
                    buffer[k++] = '#';
                    break;
                }
            }
        }
    } // while
    buffer[k] = '\0';
}

#define MAX_MSG_SIZE 1000
void fmuLogger(void *componentEnvironment, fmi2String instanceName, fmi2Status status,
               fmi2String category, fmi2String message, ...) {
    char msg[MAX_MSG_SIZE];
    char* copy;
    va_list argp;

    // replace C format strings
    va_start(argp, message);
    vsprintf(msg, message, argp);
    va_end(argp);

    // replace e.g. ## and #r12#
    copy = strdup(msg);
//    replaceRefsInMessage(copy, msg, MAX_MSG_SIZE, NULL);
    free(copy);

    // print the final message
    if (!instanceName) instanceName = "?";
    if (!category) category = "?";
    printf("%s %s (%s): %s\n", fmi2StatusToString(status), instanceName, category, msg);
}

int error(const char* message){
    printf("%s\n", message);
    return 0;
}
//
//void parseArguments(int argc, char *argv[], const char **fmuFileName, double *tEnd, double *h,
//                    int *loggingOn, char *csv_separator, int *nCategories, char **logCategories[]) {
//    // parse command line arguments
//    if (argc > 1) {
//        *fmuFileName = argv[1];
//    } else {
//        printf("error: no fmu file\n");
//        printHelp(argv[0]);
//        exit(EXIT_FAILURE);
//    }
//    if (argc > 2) {
//        if (sscanf(argv[2],"%lf", tEnd) != 1) {
//            printf("error: The given end time (%s) is not a number\n", argv[2]);
//            exit(EXIT_FAILURE);
//        }
//    }
//    if (argc > 3) {
//        if (sscanf(argv[3],"%lf", h) != 1) {
//            printf("error: The given stepsize (%s) is not a number\n", argv[3]);
//            exit(EXIT_FAILURE);
//        }
//    }
//    if (argc > 4) {
//        if (sscanf(argv[4],"%d", loggingOn) != 1 || *loggingOn < 0 || *loggingOn > 1) {
//            printf("error: The given logging flag (%s) is not boolean\n", argv[4]);
//            exit(EXIT_FAILURE);
//        }
//    }
//    if (argc > 5) {
//        if (strlen(argv[5]) != 1) {
//            printf("error: The given CSV separator char (%s) is not valid\n", argv[5]);
//            exit(EXIT_FAILURE);
//        }
//        switch (argv[5][0]) {
//            case 'c': *csv_separator = ','; break; // comma
//            case 's': *csv_separator = ';'; break; // semicolon
//            default:  *csv_separator = argv[5][0]; break; // any other char
//        }
//    }
//    if (argc > 6) {
//        int i;
//        *nCategories = argc - 6;
//        *logCategories = (char **)calloc(sizeof(char *), *nCategories);
//        for (i = 0; i < *nCategories; i++) {
//            (*logCategories)[i] = argv[i + 6];
//        }
//    }
//}
//
//void printHelp(const char *fmusim) {
//    printf("command syntax: %s <model.fmu> <tEnd> <h> <loggingOn> <csv separator>\n", fmusim);
//    printf("   <model.fmu> .... path to FMU, relative to current dir or absolute, required\n");
//    printf("   <tEnd> ......... end  time of simulation,   optional, defaults to 1.0 sec\n");
//    printf("   <h> ............ step size of simulation,   optional, defaults to 0.1 sec\n");
//    printf("   <loggingOn> .... 1 to activate logging,     optional, defaults to 0\n");
//    printf("   <csv separator>. separator in csv file,     optional, c for ',', s for';', defaults to c\n");
//    printf("   <logCategories>. list of active categories, optional, see modelDescription.xml for possible values\n");
//}
