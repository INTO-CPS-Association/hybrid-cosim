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
project (Controller C CXX)

# HOW to
#
# cmake -DCMAKE_TOOLCHAIN_FILE=msys-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug .
# make
# 
# to list dependencies use:
#  objdump -p binaries/win64/window-sa.dll |  grep 'DLL Name:'
#

include_directories(fmi2)

if (WIN32)
	#windows, becuase windows just cannot figure out to do it correct. 
	# must be a bug in msys mingw gcc 6.3	
	# it doesnt read the rsp files.
	set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
	set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES 0)
	
	set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
	set(CMAKE_C_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
endif() 


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

file(GLOB C_FILES sources/*.c)

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
file(MAKE_DIRECTORY ${FMI_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FMI_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FMI_BIN_DIR})

add_library(${PROJECT_NAME} SHARED ${C_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")



# I need this: -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

if (WIN32)
	#windows	
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc  -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
endif() 


add_custom_target(pack COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" ${PROJECT_NAME}.fmu --format=zip
       "${CMAKE_CURRENT_SOURCE_DIR}/modelDescription.xml"
        "${FMI_BIN_DIR}"
)

