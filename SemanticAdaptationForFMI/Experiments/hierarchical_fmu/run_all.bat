@echo off 

rem ------------------------------------------------------------
rem This batch runs all FMUs of the FmuSDK and stores simulation
rem results in CSV files, one file per simulation run.
rem Command to run the 32 bit version: run_all
rem Command to run the 64 bit version: run_all -win64
rem Copyright QTronic GmbH. All rights reserved.
rem ------------------------------------------------------------

setlocal

echo Running all FMUs 2.0 of the FmuSDK ...

call run_mass_spring_damper %1

call run_mass_spring_damper_hierarchical %1

endlocal

