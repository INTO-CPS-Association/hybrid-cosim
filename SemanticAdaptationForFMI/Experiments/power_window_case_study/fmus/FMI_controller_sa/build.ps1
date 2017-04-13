rm "Debug\*"

mingw32-make clean makefile
mingw32-make lib makefile

copy ..\FMI_controller\Debug\* .\Debug\

pause