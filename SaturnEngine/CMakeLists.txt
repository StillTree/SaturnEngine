#Link libraries
add_subdirectory(libs)

#SaturnEngine stuff
option(ST_BUILD_SHARED "Build the engine as a dynamic link library." OFF)
option(ST_BUILD_EXAMPLES "Build the example projects." OFF)

file(GLOB_RECURSE SaturnEngine_INCLUDE include/*.h)
file(GLOB_RECURSE SaturnEngine_SOURCE src/*.cpp)

set(SaturnEngine_INCLUDE_DIRECTORIES
		include
		libs/spdlog/include
		libs/rapidJSON/include)

if(ST_BUILD_SHARED)
	add_library(SaturnEngine SHARED ${SaturnEngine_SOURCE} ${SaturnEngine_INCLUDE})
	target_compile_definitions(SaturnEngine PUBLIC ST_BUILD_SHARED)
else()
	add_library(SaturnEngine STATIC ${SaturnEngine_SOURCE} ${SaturnEngine_INCLUDE})
	target_compile_definitions(SaturnEngine PUBLIC ST_BUILD_STATIC)
endif()

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

target_precompile_headers(SaturnEngine PUBLIC include/SaturnEngine/SaturnPrecompiled.h)
target_compile_definitions(SaturnEngine PRIVATE ST_LIBRARY)
target_include_directories(SaturnEngine PUBLIC ${SaturnEngine_INCLUDE_DIRECTORIES})
set_target_properties(SaturnEngine PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(SaturnEngine PRIVATE spdlog::spdlog_header_only)
