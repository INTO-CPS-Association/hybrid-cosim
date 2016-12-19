@echo off 

rem ------------------------------------------------------------
rem This batch builds both simulators and all FMUs of the FmuSDK
rem Copyright QTronic GmbH. All rights reserved.
rem ------------------------------------------------------------

rem First argument %1 should be empty for win32, and '-win64' for win64 build.
call build_fmusim_cs %1
echo -----------------------------------------------------------
echo Making the FMUs of the FmuSDK ...
pushd models

call build_fmu cs mass_spring_damper_hierarchical %1

popd

pause