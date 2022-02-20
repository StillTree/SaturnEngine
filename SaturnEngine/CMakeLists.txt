#Link SPDLOG
add_subdirectory(libs/spdlog)

#Link JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(libs/json)

#SaturnEngine stuff
file(GLOB_RECURSE SaturnEngine_INCLUDE include/*.h)
file(GLOB_RECURSE SaturnEngine_SOURCE src/*.cpp)

set(SaturnEngine_INCLUDE_DIRECTORIES
		include
		libs/spdlog/include
		libs/json/include)

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
set_target_properties(SaturnEngine PROPERTIES LINKER_LANGUAGE CXX)
