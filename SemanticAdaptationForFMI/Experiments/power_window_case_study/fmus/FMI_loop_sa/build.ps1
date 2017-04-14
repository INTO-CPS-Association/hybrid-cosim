rm "Debug\*"

mingw32-make clean makefile
mingw32-make lib makefile

pause

Echo "Exporting dependencies..."

Push-Location ..\FMI_Window_sa\
	& .\build.ps1
Pop-Location

copy ..\FMI_Window_sa\Debug\* .\Debug\
copy ..\ThirdParty\FMI_Obstacle\binaries\win32\*.dll Debug\

pause