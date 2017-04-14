rm "Debug\*"

mingw32-make clean makefile
mingw32-make lib makefile

copy ..\ThirdParty\FMI_Window\binaries\win32\*.dll Debug\

pause