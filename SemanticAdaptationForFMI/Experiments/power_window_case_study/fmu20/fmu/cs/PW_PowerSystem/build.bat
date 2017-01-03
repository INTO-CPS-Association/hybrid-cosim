@echo off

mode 230,1000

setlocal

set PATH=%PATH%;C:\MinGW\msys\1.0\bin

pushd sources

make clean

make

popd

if "%1"=="nopause" goto skip
	pause
:skip

