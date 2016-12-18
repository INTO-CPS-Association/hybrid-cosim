@echo off 
rem ------------------------------------------------------------
rem This batch builds the FMU simulator fmu10sim_cs.exe
rem Copyright QTronic GmbH. All rights reserved
rem ------------------------------------------------------------

setlocal

echo -----------------------------------------------------------
echo building fmu10sim_cs.exe - FMI for Co-Simulation 1.0
echo -----------------------------------------------------------

rem save env variable settings
set PREV_PATH=%PATH%
if defined INCLUDE set PREV_INCLUDE=%INLUDE%
if defined LIB     set PREV_LIB=%LIB%
if defined LIBPATH set PREV_LIBPATH=%LIBPATH%

if "%1"=="-win64" (set x64=x64\) else set x64=

rem setup the compiler
if defined x64 (
if not exist ..\..\bin\x64 mkdir ..\..\bin\x64
if defined VS110COMNTOOLS (call "%VS110COMNTOOLS%\..\..\VC\vcvarsall.bat" x86_amd64) else ^
if defined VS100COMNTOOLS (call "%VS100COMNTOOLS%\..\..\VC\vcvarsall.bat" x86_amd64) else ^
if defined VS90COMNTOOLS (call "%VS90COMNTOOLS%\..\..\VC\vcvarsall.bat" x86_amd64) else ^
if defined VS80COMNTOOLS (call "%VS80COMNTOOLS%\..\..\VC\vcvarsall.bat" x86_amd64) else ^
goto noCompiler
) else (
if defined VS110COMNTOOLS (call "%VS110COMNTOOLS%\vsvars32.bat") else ^
if defined VS100COMNTOOLS (call "%VS100COMNTOOLS%\vsvars32.bat") else ^
if defined VS90COMNTOOLS (call "%VS90COMNTOOLS%\vsvars32.bat") else ^
if defined VS80COMNTOOLS (call "%VS80COMNTOOLS%\vsvars32.bat") else ^
goto noCompiler
)

set SRC=fmusim_cs\main.c ..\shared\xmlVersionParser.c ..\shared\xml_parser.c ..\shared\stack.c ..\shared\sim_support.c
set INC=/Iinclude /I../shared /Ifmusim_cs
set OPTIONS=/DSTANDALONE_XML_PARSER /nologo /DFMI_COSIMULATION /DLIBXML_STATIC

rem create fmu10sim_cs.exe in the fmusim_cs dir
pushd co_simulation
cl %SRC% %INC% %OPTIONS% /Fefmu10sim_cs.exe /link ..\shared\%x64%libexpatMT.lib /LIBPATH:..\shared\%x64%
del *.obj
popd
if not exist co_simulation\fmu10sim_cs.exe goto compileError
move /Y co_simulation\fmu10sim_cs.exe ..\..\bin\%x64%
goto done

:noCompiler
echo No Microsoft Visual C compiler found

:compileError
echo build of fmu10sim_cs.exe failed

:done
rem undo variable settings performed by vsvars32.bat
set PATH=%PREV_PATH%
if defined PREV_INCLUDE set INCLUDE=%PREV_INLUDE%
if defined PREV_LIB     set LIB=%PREV_LIB%
if defined PREV_LIBPATH set LIBPATH=%PREV_LIBPATH%
echo done.

endlocal
