#Link SPDLOG
add_subdirectory(libs/spdlog)

#Link JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(libs/json)

#SaturnEngine stuff
set(SaturnEngine_SOURCE
		src/SaturnEngine/StartUp.cpp
		src/Management/LogManager.cpp
		src/Management/FrameAllocator.cpp
		src/Utils/File.cpp
		src/Management/ErrorManager.cpp
		src/Utils/String.cpp
		src/SaturnEngine/Window.cpp)

set(SaturnEngine_INCLUDE
		include/SaturnEngine.h
		include/SaturnEngine/Core.h
		include/SaturnEngine/StartUp.h
		include/Management/LogManager.h
		include/Management/FrameAllocator.h
		include/Utils/File.h
		include/Management/ErrorManager.h
		include/Utils/String.h
		include/SaturnEngine/Events/Event.h
		include/SaturnEngine/Events/EventSender.h
		include/SaturnEngine/Window.h include/SaturnEngine/Events/WindowEvents.h include/SaturnEngine/GlobalDataStructs.h)

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
