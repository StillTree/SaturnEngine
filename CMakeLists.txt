cmake_minimum_required(VERSION 3.2)

project(SaturnEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#Saturn Engine stuff
add_library(SaturnEngine SHARED SaturnEngine/src/SaturnEngine.h
		SaturnEngine/src/SaturnEngine/Core.h
		SaturnEngine/src/SaturnEngine/StartUp.h
		SaturnEngine/src/SaturnEngine/StartUp.cpp
		SaturnEngine/src/SaturnEngine/Errors.h
		SaturnEngine/src/Management/LogManager.cpp
		SaturnEngine/src/Management/LogManager.h)

if(WIN32)
	target_compile_definitions(SaturnEngine PUBLIC ST_WINDOWS)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(SaturnEngine PRIVATE ST_DEBUG)
endif()

target_include_directories(SaturnEngine PUBLIC SaturnEngine/libs/spdlog/include)
target_compile_definitions(SaturnEngine PRIVATE ST_LIBRARY)

#Application stuff
add_executable(AppSandbox AppSandbox/src/AppSandbox.cpp)

target_link_libraries(AppSandbox PUBLIC SaturnEngine)
target_include_directories(AppSandbox PUBLIC SaturnEngine/src)
target_compile_definitions(AppSandbox PUBLIC ST_EXECUTABLE)
