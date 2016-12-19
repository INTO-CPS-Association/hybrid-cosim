@echo off 

setlocal
if "%1"=="-win64" (
set x64=x64\
set x64NAME=x64
) else (
set x64=
set x64NAME=
)

echo Running mass_spring_damper FMUs 2.0 ...

echo -----------------------------------------------------------
call fmusim cs20 fmu20\fmu\cs\%x64%mass_spring_damper.fmu 4 0.01 1 c %1
move /Y result.csv result_cs20%x64NAME%_mass_spring_damper.csv

endlocal

rem keep window visible for user
pause