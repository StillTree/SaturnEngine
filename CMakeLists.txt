cmake_minimum_required(VERSION 3.1...3.21)

project(SaturnEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#Saturn Engine stuff
add_library(SaturnEngine SHARED SaturnEngine/include/SaturnEngine.h
		SaturnEngine/include/SaturnEngine/Core.h
		SaturnEngine/include/SaturnEngine/StartUp.h
		SaturnEngine/src/SaturnEngine/StartUp.cpp
		SaturnEngine/include/SaturnEngine/Errors.h
		SaturnEngine/src/Management/LogManager.cpp
		SaturnEngine/include/Management/LogManager.h
		SaturnEngine/include/Management/FrameAllocator.h
		SaturnEngine/src/Management/FrameAllocator.cpp)

if(WIN32)
	target_compile_definitions(SaturnEngine PUBLIC ST_WINDOWS)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(SaturnEngine PRIVATE ST_DEBUG)
endif()

target_compile_definitions(SaturnEngine PRIVATE ST_LIBRARY)
target_include_directories(SaturnEngine PUBLIC SaturnEngine/libs/spdlog/include)
target_include_directories(SaturnEngine PUBLIC SaturnEngine/include)

#Application stuff
add_executable(AppSandbox AppSandbox/src/AppSandbox.cpp)

target_link_libraries(AppSandbox PUBLIC SaturnEngine)
target_compile_definitions(AppSandbox PUBLIC ST_EXECUTABLE)
