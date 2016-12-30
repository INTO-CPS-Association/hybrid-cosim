@echo off 

xcopy "%TEMP%\OpenModelica\OMEdit\PW_PowerSystem.fmu" .\fmu20\fmu\cs\ /Y /D
xcopy "%TEMP%\OpenModelica\OMEdit\PW_Window.fmu" .\fmu20\fmu\cs\ /Y /D
xcopy "%TEMP%\OpenModelica\OMEdit\Obstacle.fmu" .\fmu20\fmu\cs\ /Y /D
xcopy "%TEMP%\OpenModelica\OMEdit\Echo.fmu" .\fmu20\fmu\cs\ /Y /D

pause