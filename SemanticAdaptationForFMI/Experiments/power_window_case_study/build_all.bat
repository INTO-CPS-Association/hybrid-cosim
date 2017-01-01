@echo off 

echo -----------------------------------------------------------
echo Making the simulators and models for FMI 2.0 ...
copy ..\hierarchical_fmu\fmu20\fmu\cs\mass_spring_damper.fmu .\fmu20\fmu\cs\
pushd fmu20\src
call build_all %1
popd
echo Making the simulators and models for FMI 2.0 ... DONE!
echo -----------------------------------------------------------
