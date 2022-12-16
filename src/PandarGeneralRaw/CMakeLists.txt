cmake_minimum_required(VERSION 2.8)
project(PandarGeneral)

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

find_package(PCL REQUIRED COMPONENTS common)

set (CMAKE_CXX_FLAGS "-fPIC --std=c++17")

include_directories(
	.
	include
	include/pandarGeneral
	${PCL_INCLUDE_DIRS}
)


add_library( ${PROJECT_NAME}
	src/input.cc
	src/pandarGeneral_internal.cc
	src/pandarGeneral.cc
        src/pcap_reader.cpp
)


if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "lessgooo: ${PCL_INCLUDE_DIRS}")