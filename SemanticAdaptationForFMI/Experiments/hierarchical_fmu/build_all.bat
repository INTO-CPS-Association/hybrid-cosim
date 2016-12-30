@echo off 

echo -----------------------------------------------------------
echo Making the simulators and models for FMI 2.0 ...
pushd fmu20\src
call build_all %1
popd

