@echo off

mode 230,10000

FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_statemachine.txt"  -l 6  -o "results_statemachine.csv"  "StategraphSample.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_example.txt"  -l 6  -o "results_example.csv"  "Modelica_Electrical_Machines_Examples_DCMachines_DCEE_Start.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_echo.txt"  -l 6  -o "results_echo.csv"  "Echo.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_msd.txt"  -l 6  -o "results_msd.csv"  "mass_spring_damper.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_obstacle.txt"  -l 6  -o "results_obstacle.csv"  "Obstacle.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_window.txt"  -l 6  -o "results_window.csv"  "PW_Window.fmu"

if "%1"=="nopause" goto skip
	pause
:skip

