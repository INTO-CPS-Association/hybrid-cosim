package be.uantwerpen.ansymo.semanticadaptation.testframework

class StaticGenerators {
	def static String generateMainCppFile(String folderPath)
	{
		'''
		/*
		 * main.cpp
		 *
		 *  Created on: Mar 14, 2017
		 *      Author: kel
		 */
		#include <iostream>
		#include "fmi2TypesPlatform.h"
		#include "fmi2Functions.h"
		#include <string>
		
		#include <memory>
		#include <iostream>
		
		#include <cstdio>
		#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
		#include <fstream>
		
		using namespace std;
		
		void fmuLoggerCache(void *componentEnvironment, fmi2String instanceName,
				fmi2Status status, fmi2String category, fmi2String message, ...) {
			va_list argp;
		
			// replace C format strings
			va_start(argp, message);
			size_t size = vsnprintf(nullptr, 0, message, argp) + 1; // Extra space for '\0'
			va_end(argp);
		
			va_start(argp, message);
			unique_ptr<char[]> buf(new char[size]);
			vsnprintf(buf.get(), size, message, argp);
			va_end(argp);
		
			string completeMessage = string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		
			cout << "FROM MAIN: Name: " << instanceName << " Status: " << status << " Category: "
					<< category << " Msg: " << completeMessage << endl;
		}
		
		fmi2Status setReal(fmi2Component comp, fmi2ValueReference id, fmi2Real val) {
			const fmi2ValueReference vr[] { id };
			size_t nvr = 1;
			fmi2Real value[] { val };
			return fmi2SetReal(comp, vr, nvr, value);
		}
		
		fmi2Real getReal(fmi2Component comp, fmi2ValueReference id) {
			const fmi2ValueReference vr[] { id };
			size_t nvr = 1;
			fmi2Real value[1];
			fmi2GetReal(comp, vr, nvr, value);
		
			return value[0];
		}
		
		int main(int argc, char *argv[]) {
		//	setvbuf(stdout, NULL, _IONBF, 0);
		//	setvbuf(stderr, NULL, _IONBF, 0);
		
			cout << "hello" << endl;
		
			fmi2CallbackFunctions callback = { &fmuLoggerCache, NULL, NULL, NULL, NULL };
			fmi2Component comp =
					fmi2Instantiate("this system", fmi2CoSimulation, "{1234}",
							"«folderPath»",
							&callback, fmi2True,
							fmi2True);
		
			if (comp == NULL) {
				cout << "init failed" << endl;
				return -1;
			}
		
			if (fmi2SetupExperiment(comp, false, 0.0, 0, true, 100) != fmi2OK) {
				printf("Error fmi2SetupExperiment");
				return 1;
			}
		
			if (fmi2EnterInitializationMode(comp) != fmi2OK) {
				printf("Error fmi2SetupExperiment");
				return 1;
			}
		
			if (fmi2ExitInitializationMode(comp) != fmi2OK) {
				printf("Error fmi2SetupExperiment");
				return 1;
			}
		
		#define ID_Window_SA_IN_reaction_force 0
		#define ID_Window_SA_IN_displacement 1
		#define ID_Window_SA_IN_speed 2
		
		#define ID_Window_SA_OUT_disp 3
		#define ID_Window_SA_OUT_tau 4
		
			std::fstream fs;
			fs.open("result.csv",
					std::fstream::in | std::fstream::out | std::fstream::trunc);
		
			//cout << "------------ Header ---------" << endl;
			fs << "\"time\",\"ID_Window_SA_OUT_disp\",\"ID_Window_SA_OUT_tau\"" << endl;
			double time = 0.0;
			double stepSize = 0.01;
		
			for (double time = 0.0; time < 10;) {
				if (setReal(comp, ID_Window_SA_IN_reaction_force, -1.0) != fmi2OK) {
					printf("Error setting real");
					return 1;
				}
				if (setReal(comp, ID_Window_SA_IN_displacement, time) != fmi2OK) {
					printf("Error setting real");
					return 1;
				}
				if (setReal(comp, ID_Window_SA_IN_speed, 1.0) != fmi2OK) {
					printf("Error setting real");
					return 1;
				}
		
				if (fmi2DoStep(comp, time, stepSize, false) != fmi2OK) {
					printf("Errorin do step");
					return 1;
				}
				time += stepSize;
		
				auto disp = getReal(comp, ID_Window_SA_OUT_disp);
				auto tau = getReal(comp, ID_Window_SA_OUT_tau);
		
				cout << "time: " << time << " disp: " << disp << " tau: " << tau
						<< endl;
				fs << time << "," << disp << "," << tau << endl;
			}
			fs.close();
		
			return 0;
		}
		
		'''
	}

	def static String generateCMakeLists(String projectName, String frameworkPath)
	{
		'''
		#
		# #%~
		# The Overture Abstract Syntax Tree
		# %%
		# Copyright (C) 2017 - 2014 Aarhus University
		# %%
		# This program is free software: you can redistribute it and/or modify
		# it under the terms of the GNU General Public License as
		# published by the Free Software Foundation, either version 3 of the
		# License, or (at your option) any later version.
		# 
		# This program is distributed in the hope that it will be useful,
		# but WITHOUT ANY WARRANTY; without even the implied warranty of
		# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		# GNU General Public License for more details.
		# 
		# You should have received a copy of the GNU General Public
		# License along with this program.  If not, see
		# <http://www.gnu.org/licenses/gpl-3.0.html>.
		# #~%
		#
		cmake_minimum_required (VERSION 3.5.2)
		# this (3.5.2) is the first version where External Project uses --recursive
		project («projectName» C CXX)
		
		# HOW to
		#
		# cmake -DCMAKE_TOOLCHAIN_FILE=msys-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug .
		# make
		# 
		# to list dependencies use:
		#  objdump -p binaries/win64/window-sa.dll |  grep 'DLL Name:'
		#
		
		
		
		if (WIN32)
			#windows, becuase windows just cannot figure out to do it correct. 
			# must be a bug in msys mingw gcc 6.3	
			# it doesnt read the rsp files.
			set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
			set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES 0)
			
			set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
			set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
		endif() 
		
		
		# Checkout the hcf sources
		set(HCF_DIR hcf)
		if(EXISTS ${HCF_DIR})
			#execute_process(COMMAND git pull WORKING_DIRECTORY ${HCF_DIR})
		else()
			execute_process(COMMAND git clone --depth 1 git@github.com:into-cps/hybridCosimulation-framework.git ${HCF_DIR} )
			execute_process(COMMAND git submodule update --init --recursive WORKING_DIRECTORY ${HCF_DIR})
		endif()
		add_subdirectory(${HCF_DIR}/semantic-adaptation)
		
		include(CheckCXXCompilerFlag)
		
		
		CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
		CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
		if(COMPILER_SUPPORTS_CXX11)
		  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		elseif(COMPILER_SUPPORTS_CXX0X)
		  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
		else()
		  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
		endif()
		
		add_definitions(-DFMI_COSIMULATION)
		
		include_directories(sources)
		
		file(GLOB CPP_FILES sources/*.cpp)
		
		file(GLOB CPP_MAIN_FILES sources/main*.cpp)
		
		list(REMOVE_ITEM CPP_FILES ${CPP_MAIN_FILES})
		
		## library ##
		
		#determine the library path
		set(FMI_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/binaries")
		
		if(WIN32 OR MINGW)
			set(FMI_BIN_DIR "${FMI_BIN_DIR}/win")
			# not sure why this doesnt work on MSYS so we just reset it
			SET (CMAKE_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITECTURE}")
		endif()
		
		if(APPLE)
			set(FMI_BIN_DIR "${FMI_BIN_DIR}/darwin")
		endif()
		
		if(UNIX AND NOT APPLE)
		  # for Linux, BSD, Solaris, Minix
			set(FMI_BIN_DIR "${FMI_BIN_DIR}/linux")
		endif()
		
		
		if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
		  set(FMI_BIN_DIR "${FMI_BIN_DIR}64")
		else ()
			set(FMI_BIN_DIR "${FMI_BIN_DIR}32")
		endif ()
		
		message("FMI output is ${FMI_BIN_DIR}")
		#SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
		file(MAKE_DIRECTORY ${FMI_BIN_DIR})
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FMI_BIN_DIR})
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FMI_BIN_DIR})
		
		#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bb)
		#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FMI_BIN_DIR})
		
		
		add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${CPP_FILES})
		target_link_libraries(${PROJECT_NAME} hcf)
		set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
		SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
		
		
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
		
		## Main executable ##
		add_executable(${PROJECT_NAME}_main ${CPP_MAIN_FILES} ${CPP_FILES})
		target_link_libraries(${PROJECT_NAME}_main hcf)
		
		
		# I need this: -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
		
		if (WIN32)
			#windows	
			set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc  -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
		endif() 
		
		'''
	}
	
}