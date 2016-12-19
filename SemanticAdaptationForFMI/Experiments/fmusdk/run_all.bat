@echo off 

rem ------------------------------------------------------------
rem This batch runs all FMUs of the FmuSDK and stores simulation
rem results in CSV files, one file per simulation run.
rem Command to run the 32 bit version: run_all
rem Command to run the 64 bit version: run_all -win64
rem Copyright QTronic GmbH. All rights reserved.
rem ------------------------------------------------------------

setlocal
if "%1"=="-win64" (
set x64=x64\
set x64NAME=x64
) else (
set x64=
set x64NAME=
)

echo Running all FMUs 2.0 of the FmuSDK ...

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%mass_spring_damper.fmu 4 0.01 1 c %1
move /Y result.csv result_cs20%x64NAME%_mass_spring_damper.csv

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%bouncingBall.fmu 4 0.01 1 c %1
move /Y result.csv result_cs20%x64NAME%_bouncingBall.csv

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%vanDerPol.fmu 5 0.1 1 c %1
move /Y result.csv result_cs20%x64NAME%_vanDerPol.csv

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%dq.fmu 1 0.1 1 c %1
move /Y result.csv result_cs20%x64NAME%_dq.csv

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%inc.fmu 15 0.5 1 c %1
move /Y result.csv result_cs20%x64NAME%_inc.csv

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%values.fmu 12 0.1 1 c %1
move /Y result.csv result_cs20%x64NAME%_values.csv

endlocal

rem keep window visible for user
pause