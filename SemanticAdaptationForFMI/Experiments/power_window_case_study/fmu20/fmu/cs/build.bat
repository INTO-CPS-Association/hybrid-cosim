@echo off

mode 230,1000

pushd PW_PowerSystem

call build nopause

popd

if "%1"=="nopause" goto skip
	pause
:skip

