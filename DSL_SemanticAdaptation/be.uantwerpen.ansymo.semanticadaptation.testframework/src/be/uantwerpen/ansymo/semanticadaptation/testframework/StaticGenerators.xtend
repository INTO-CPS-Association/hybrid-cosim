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
		cmake_minimum_required (VERSION 2.8.5)
		project («projectName» C CXX)
		
		include(CheckCXXCompilerFlag)
		
		#set(CMAKE_VERBOSE_MAKEFILE on)
		
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
		
		if (WIN32)
			#windows, becuase windows just cannot figure out to do it correct. 
			# must be a bug in msys mingw gcc 6.3	
			# it doesnt read the rsp files.
			set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
			set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES 0)
			
			set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
			set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
		endif()
		
		add_subdirectory («frameworkPath»)
		
		include_directories(src)
		
		
		file(GLOB CPP_FILES src/*.cpp)
		
		file(GLOB CPP_MAIN_FILES src/main*.cpp)
		
		list(REMOVE_ITEM CPP_FILES ${CPP_MAIN_FILES})
		
		## library ##
		
		add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${CPP_FILES})
		target_link_libraries(${PROJECT_NAME} hcf)
		set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
		
		
		## Main executable ##
		add_executable(${PROJECT_NAME}_main ${CPP_MAIN_FILES} ${CPP_FILES})
		target_link_libraries(${PROJECT_NAME}_main hcf)
		
		foreach(LETTER ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
			
		if(EXISTS "${LETTER}/libstdc++.a")
		#   message (STATUS "${LETTER}")
			set(STDCPP_LIBRARY "${LETTER}/libstdc++.a")
		else()
		#  message (STATUS "${LETTER} ---- not these")
		endif()
		endforeach()
		
		message(STATUS "Static linking with libstdc++.a in ${STDCPP_LIBRARY}")
		#target_link_libraries(${PROJECT_NAME} ${STDCPP_LIBRARY})
		
		
		
		# I need this: -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
		
		if (WIN32)
			#windows	
			set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
		 set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc  -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
		endif() 
		
		
		
		
		#if(NOT APPLE)
		#https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/pthread.3.html 
		#it is included in system
		find_library(PTHREAD_LIBRARY NAMES libwinpthread.dll.a)# libpthread.a libpthread.dylib )
		#message( INFO ${PTHREAD_LIBRARY})
		#target_link_libraries(${PROJECT_NAME}_main ${PTHREAD_LIBRARY} /C/msys64/mingw64/x86_64-w64-mingw32/lib/libwinpthread.a)
		#endif()
		
		#add_custom_command(${PROJECT_NAME}_main POST_BUILD COMMAND "find . -name *.exe -exec echo {} \; -exec bash -c \"objdump -p {} | grep 'DLL Name:'\" \;")		
		
		'''
	}
	
}