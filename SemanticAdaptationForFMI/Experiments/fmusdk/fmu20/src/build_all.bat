@echo off 

rem First argument %1 should be empty for win32, and '-win64' for win64 build.
call build_mass_spring_damper %1
call build_mass_spring_damper_hierarchical %1


