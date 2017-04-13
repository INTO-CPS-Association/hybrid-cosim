mingw32-make clean makefile
mingw32-make exe makefile

pause

$LibAbsolutionPath = (Get-Item -Path ".\Debug" -Verbose).FullName

Echo "Building FMUs and getting their dlls..."

Push-Location ..\fmus
    $FMUSources = Get-ChildItem -Filter FMI_*
    ForEach ($fmu In $FMUSources){
        Push-Location $fmu
            & .\build.ps1
            $generated_dlls = Get-ChildItem Debug -Filter *.dll
            ForEach ($dll In $generated_dlls){
                copy "Debug\$dll" "$LibAbsolutionPath"
            }
        Pop-Location
    }
Pop-location

Echo "Building FMUs and getting their dlls... DONE."

Echo "Gettings dlls from third party FMUs..."
Push-Location ..\fmus\ThirdParty
    $FMUSources = Get-ChildItem -dir -Filter FMI_*
    ForEach ($fmu In $FMUSources){
        Push-Location $fmu\binaries\win32
            copy * "$LibAbsolutionPath"
        Pop-Location
    }
Pop-location
Echo "Gettings dlls from third party FMUs... DONE."

pause
