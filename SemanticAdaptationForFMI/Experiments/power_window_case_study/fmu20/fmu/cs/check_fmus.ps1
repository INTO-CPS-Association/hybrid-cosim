param (
	[switch]$nopause = $false
)

FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_power_standalone.txt"  -l 6  -o "results_power_stand_alone.csv"  "PowerSystemStandAlone.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_echo.txt"  -l 6  -o "results_echo.csv"  "Echo.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_msd.txt"  -l 6  -o "results_msd.csv"  "mass_spring_damper.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_obstacle.txt"  -l 6  -o "results_obstacle.csv"  "Obstacle.fmu"
FMUChecker-2.0b3-win32\fmuCheck.win32.exe  -f -e "log_window.txt"  -l 6  -o "results_window.csv"  "PW_Window.fmu"

if (-not $nopause) {
    pause
}