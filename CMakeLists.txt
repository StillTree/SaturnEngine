cmake_minimum_required(VERSION 3.1...3.21)

project(SaturnEngine VERSION 0.0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#Spdlog stuff
add_subdirectory(SaturnEngine/libs/spdlog)

#JSON stuff
add_subdirectory(SaturnEngine/libs/json)

#SaturnEngine stuff
set(SaturnEngine_SOURCE
		SaturnEngine/src/SaturnEngine/StartUp.cpp
		SaturnEngine/src/Management/LogManager.cpp
		SaturnEngine/src/Management/FrameAllocator.cpp
		SaturnEngine/src/Utils/File.cpp
		SaturnEngine/src/Management/ErrorManager.cpp
		SaturnEngine/src/Utils/String.cpp)

set(SaturnEngine_INCLUDE
		SaturnEngine/include/SaturnEngine.h
		SaturnEngine/include/SaturnEngine/Core.h
		SaturnEngine/include/SaturnEngine/StartUp.h
		SaturnEngine/include/Management/LogManager.h
		SaturnEngine/include/Management/FrameAllocator.h
		SaturnEngine/include/Utils/File.h
		SaturnEngine/include/Management/ErrorManager.h
		SaturnEngine/include/Utils/String.h)

set(SaturnEngine_INCLUDE_DIRECTORIES
		SaturnEngine/include
		SaturnEngine/libs/spdlog/include
		SaturnEngine/libs/json/include)

add_library(SaturnEngine SHARED ${SaturnEngine_SOURCE} ${SaturnEngine_INCLUDE})

if(WIN32 AND CMAKE_SIZEOF_VOID_P MATCHES 8)
	target_compile_definitions(SaturnEngine PUBLIC ST_WINDOWS)
else()
	message(FATAL_ERROR "Saturn Engine currently supports only Windows x64.")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(SaturnEngine PUBLIC ST_BUILD_DEBUG)
else()
	target_compile_definitions(SaturnEngine PUBLIC ST_BUILD_RELEASE)
endif()

target_compile_definitions(SaturnEngine PRIVATE ST_LIBRARY)
target_link_libraries(SaturnEngine PRIVATE spdlog::spdlog_header_only nlohmann_json::nlohmann_json)
target_include_directories(SaturnEngine PUBLIC ${SaturnEngine_INCLUDE_DIRECTORIES})

#AppSandbox stuff
set(AppSandbox_SOURCE AppSandbox/src/AppSandbox.cpp)

set(AppSandbox_INCLUDE)

add_executable(AppSandbox ${AppSandbox_SOURCE} ${AppSandbox_INCLUDE})

target_link_libraries(AppSandbox PUBLIC SaturnEngine)
target_compile_definitions(AppSandbox PUBLIC ST_EXECUTABLE)

#Utilities
set_target_properties(SaturnEngine AppSandbox PROPERTIES LINKER_LANGUAGE CXX)
include(cmake/ide.cmake)
