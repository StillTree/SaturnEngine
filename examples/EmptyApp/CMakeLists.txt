project(EmptyApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(EmptyApp src/Main.cpp)
target_link_libraries(EmptyApp SaturnEngine)

if(ST_BUILD_SHARED)
	set_target_properties(EmptyApp PROPERTIES ARCHIVE_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine>
		LIBRARY_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine> RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine>)
endif()
