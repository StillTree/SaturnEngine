cmake_minimum_required(VERSION 3.10...3.21)

project(SaturnEngine VERSION 0.0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#Include Saturn Engine
add_subdirectory(SaturnEngine)

#Examples of how to use Saturn Engine
if(ST_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

#Utilities for IDEs
include(cmake/ide.cmake)
