cmake_minimum_required(VERSION 3.1...3.21)

project(SaturnEngine VERSION 0.0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#Link Saturn Engine
add_subdirectory(SaturnEngine)

#Link AppSandbox
add_subdirectory(AppSandbox)

#Utilities
include(cmake/ide.cmake)
