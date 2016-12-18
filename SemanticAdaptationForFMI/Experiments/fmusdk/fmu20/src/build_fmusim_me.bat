@echo off 
rem ------------------------------------------------------------
rem This batch builds the FMU simulator fmu20sim_me.exe
rem Usage: build_fmusim_cs.bat (-win64)
rem Copyright QTronic GmbH. All rights reserved
rem ------------------------------------------------------------

setlocal

echo -----------------------------------------------------------
echo building fmu20sim_me.exe - FMI for Model Exchange 2.0
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

set SRC=main.c ..\shared\sim_support.c ..\shared\xmlVersionParser.c ..\shared\parser\XmlParser.cpp ..\shared\parser\XmlElement.cpp ..\shared\parser\XmlParserCApi.cpp
set INC=/I..\shared\include /I..\shared /I..\shared\parser
set OPTIONS= /nologo /EHsc /DSTANDALONE_XML_PARSER /DLIBXML_STATIC

rem create fmu20sim_me.exe in the model_exchange dir
pushd model_exchange
cl %SRC% %INC% %OPTIONS% /Fefmu20sim_me.exe /link /LIBPATH:..\shared\parser\%x64%
del *.obj
popd
if not exist model_exchange\fmu20sim_me.exe goto compileError
move /Y model_exchange\fmu20sim_me.exe ..\..\bin\%x64%
goto done

:noCompiler
echo No Microsoft Visual C compiler found

:compileError
echo build of fmu20sim_me.exe failed

:done
rem undo variable settings performed by vsvars32.bat
set PATH=%PREV_PATH%
if defined PREV_INCLUDE set INCLUDE=%PREV_INLUDE%
if defined PREV_LIB     set LIB=%PREV_LIB%
if defined PREV_LIBPATH set LIBPATH=%PREV_LIBPATH%
echo done.

endlocal