CC=gcc
AR=@AR@
CFLAGS=${SIM_OR_DYNLOAD_OPT_LEVEL} -falign-functions -msse2 -mfpmath=sse -g  -D USE_DEBUG_TRACE=1
LD=$(CC) -shared
LDFLAGS=-L"C:\OpenModelica1.12.0-dev-32bit\tools\msys\mingw32\lib" -L"C:\OpenModelica1.12.0-dev-32bit\lib\omc" -lregex -lexpat -lomcgc -lpthread -fopenmp -loleaut32 -lz -lhdf5  -lSimulationRuntimeC -lomcgc -lexpat -lregex -static-libgcc -luuid -loleaut32 -lole32 -lws2_32 -llis -lumfpack -lklu -lcolamd -lbtf -lamd -lsundials_idas -lsundials_kinsol -lsundials_nvecserial -lipopt -lcoinmumps -lpthread -lm -lgfortranbegin -lgfortran -lmingw32 -lgcc_eh -lmoldname -lmingwex -lmsvcrt -luser32 -lkernel32 -ladvapi32 -lshell32 -lopenblas -lcminpack -lwsock32 -lstdc++ 
DLLEXT=.dll
NEED_RUNTIME=
NEED_DGESV=
FMIPLATFORM=win32
# Note: Simulation of the fmu with dymola does not work with -finline-small-functions (enabled by most optimization levels)
CPPFLAGS=
OMC_NUM_LINEAR_SYSTEMS=6
OMC_NUM_NONLINEAR_SYSTEMS=0
OMC_NUM_MIXED_SYSTEMS=0
OMC_NDELAY_EXPRESSIONS=0
OMC_NVAR_STRING=0

override CPPFLAGS += -I include/  -I ./  -D OMC_MODEL_PREFIX=PW_PowerSystem  -D OMC_NUM_MIXED_SYSTEMS=0  -D USE_DEBUG_TRACE -D OMC_NUM_LINEAR_SYSTEMS=6  -D OMC_NUM_NONLINEAR_SYSTEMS=0  -D OMC_NDELAY_EXPRESSIONS=0  -D OMC_NVAR_STRING=0

MAINFILE=PW_PowerSystem_FMU.c
MAINOBJ=PW_PowerSystem_FMU.o
CFILES=PW_PowerSystem.c PW_PowerSystem_functions.c PW_PowerSystem_records.c \
PW_PowerSystem_01exo.c PW_PowerSystem_02nls.c PW_PowerSystem_03lsy.c PW_PowerSystem_04set.c PW_PowerSystem_05evt.c PW_PowerSystem_06inz.c PW_PowerSystem_07dly.c \
PW_PowerSystem_08bnd.c PW_PowerSystem_09alg.c PW_PowerSystem_10asr.c PW_PowerSystem_11mix.c PW_PowerSystem_12jac.c PW_PowerSystem_13opt.c PW_PowerSystem_14lnz.c \
PW_PowerSystem_15syn.c PW_PowerSystem_16dae.c PW_PowerSystem_init_fmu.c include/util/omc_error.c include/simulation/solver/initialization/initialization.c
OFILES=$(CFILES:.c=.o)
GENERATEDFILES=$(MAINFILE) PW_PowerSystem_literals.h PW_PowerSystem_model.h PW_PowerSystem_includes.h PW_PowerSystem_functions.h  PW_PowerSystem_11mix.h PW_PowerSystem_12jac.h PW_PowerSystem_13opt.h PW_PowerSystem_init_fmu.c PW_PowerSystem_info.c $(CFILES) PW_PowerSystem_FMU.libs

# FIXME: before you push into master...
RUNTIMEDIR=include
OMC_MINIMAL_RUNTIME=1
OMC_FMI_RUNTIME=1
include $(RUNTIMEDIR)/Makefile.objs
ifneq ($(NEED_RUNTIME),)
RUNTIMEFILES=$(FMI_ME_OBJS:%=$(RUNTIMEDIR)/%.o)
endif

PHONY: PW_PowerSystem_FMU
PW_PowerSystem_FMU: $(MAINOBJ) PW_PowerSystem_functions.h  PW_PowerSystem_literals.h $(OFILES) $(RUNTIMEFILES) include/fmi2/fmu2_model_interface.c
	$(CXX) -shared -I. -o PW_PowerSystem$(DLLEXT) $(MAINOBJ) $(RUNTIMEFILES) $(OFILES) $(CPPFLAGS) -L"C:/Users/clagms/Source Control/Git_HybridCosimulation/ModelicaModels"   $(CFLAGS) $(LDFLAGS) -llis -Wl,--kill-at
	rm -rf ../binaries/win32
	mkdir.exe -p ../binaries/win32
	# dlltool -d PW_PowerSystem.def --dllname PW_PowerSystem$(DLLEXT) --output-lib PW_PowerSystem.lib --kill-at
	cp PW_PowerSystem$(DLLEXT) PW_PowerSystem.lib PW_PowerSystem_FMU.libs ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libsundials_*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libopenblas.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libexpat*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libgfortran*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libquadmath*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libwinpthread*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/zlib*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libszip*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libhdf5*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libsystre*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libtre*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libintl*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libiconv*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libgcc_s_*.dll ../binaries/win32/
	cp C:/OpenModelica1.12.0-dev-32bit//bin/libstdc*.dll ../binaries/win32/
	# rm -f PW_PowerSystem.def PW_PowerSystem.o PW_PowerSystem$(DLLEXT) $(OFILES) $(RUNTIMEFILES)#
	zip -r ../../PW_PowerSystem.fmu ../*
	
clean:
	rm -f $(MAINOBJ) PW_PowerSystem.def PW_PowerSystem.o PW_PowerSystem$(DLLEXT) $(OFILES) $(RUNTIMEFILES) ../../PW_PowerSystem.fmu
	