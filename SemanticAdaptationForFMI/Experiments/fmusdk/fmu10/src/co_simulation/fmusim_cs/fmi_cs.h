/* -------------------------------------------------------------------------
 * fmi_cs.h
 * Function types for all function of the "FMI for Co-Simulation 1.0"
 * and a struct with the corresponding function pointers.
 * Copyright QTronic GmbH. All rights reserved.
 * -------------------------------------------------------------------------*/

#ifndef FMI_CS_H
#define FMI_CS_H

#include <windows.h>
#include "fmiFunctions.h"
#include "xml_parser.h"

typedef const char* (*fGetTypesPlatform)();
typedef const char* (*fGetVersion)();
typedef fmiStatus (*fSetDebugLogging)    (fmiComponent c, fmiBoolean loggingOn);
typedef fmiStatus (*fSetReal)   (fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiReal    value[]);
typedef fmiStatus (*fSetInteger)(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiInteger value[]);
typedef fmiStatus (*fSetBoolean)(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiBoolean value[]);
typedef fmiStatus (*fSetString) (fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiString  value[]);
typedef fmiStatus (*fGetReal)   (fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiReal    value[]);
typedef fmiStatus (*fGetInteger)(fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiInteger value[]);
typedef fmiStatus (*fGetBoolean)(fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiBoolean value[]);
typedef fmiStatus (*fGetString) (fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiString  value[]);
typedef fmiComponent (*fInstantiateSlave)  (fmiString  instanceName, fmiString  fmuGUID, fmiString  fmuLocation,
        fmiString  mimeType, fmiReal timeout, fmiBoolean visible, fmiBoolean interactive, 
        fmiCallbackFunctions functions, fmiBoolean loggingOn);
typedef fmiStatus (*fInitializeSlave)(fmiComponent c, fmiReal tStart, fmiBoolean StopTimeDefined, fmiReal tStop);
typedef fmiStatus (*fTerminateSlave)   (fmiComponent c);
typedef fmiStatus (*fResetSlave)       (fmiComponent c);
typedef void      (*fFreeSlaveInstance)(fmiComponent c);
typedef fmiStatus (*fSetRealInputDerivatives)(fmiComponent c, const  fmiValueReference vr[], size_t nvr,
        const fmiInteger order[], const  fmiReal value[]);
typedef fmiStatus (*fGetRealOutputDerivatives)(fmiComponent c, const fmiValueReference vr[], size_t  nvr,
        const fmiInteger order[], fmiReal value[]);
typedef fmiStatus (*fCancelStep)(fmiComponent c);
typedef fmiStatus (*fDoStep)(fmiComponent c, fmiReal currentCommunicationPoint, 
        fmiReal communicationStepSize, fmiBoolean newStep);
typedef fmiStatus (*fGetStatus)       (fmiComponent c, const fmiStatusKind s, fmiStatus*  value);
typedef fmiStatus (*fGetRealStatus)   (fmiComponent c, const fmiStatusKind s, fmiReal*    value);
typedef fmiStatus (*fGetIntegerStatus)(fmiComponent c, const fmiStatusKind s, fmiInteger* value);
typedef fmiStatus (*fGetBooleanStatus)(fmiComponent c, const fmiStatusKind s, fmiBoolean* value);
typedef fmiStatus (*fGetStringStatus) (fmiComponent c, const fmiStatusKind s, fmiString*  value);

typedef struct {
    ModelDescription* modelDescription;
    HANDLE dllHandle;
    fGetTypesPlatform getTypesPlatform;
    fGetVersion getVersion;
    fSetDebugLogging setDebugLogging;
    fSetReal setReal;
    fSetInteger setInteger;
    fSetBoolean setBoolean;
    fSetString setString;
    fGetReal getReal;
    fGetInteger getInteger;
    fGetBoolean getBoolean;
    fGetString getString;
    fInstantiateSlave instantiateSlave;
    fInitializeSlave initializeSlave;
    fTerminateSlave terminateSlave;
    fResetSlave resetSlave;
    fFreeSlaveInstance freeSlaveInstance;
    fGetRealOutputDerivatives getRealOutputDerivatives;
    fSetRealInputDerivatives setRealInputDerivatives;
    fDoStep doStep;
    fCancelStep cancelStep;
    fGetStatus getStatus;
    fGetRealStatus getRealStatus;
    fGetIntegerStatus getIntegerStatus;
    fGetBooleanStatus getBooleanStatus;
    fGetStringStatus getStringStatus;
} FMU;

#endif // FMI_CS_H

