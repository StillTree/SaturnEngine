set(AppSandbox_SOURCE src/AppSandbox.cpp)

set(AppSandbox_INCLUDE)

add_executable(AppSandbox ${AppSandbox_SOURCE} ${AppSandbox_INCLUDE})

target_link_libraries(AppSandbox PUBLIC SaturnEngine)
target_compile_definitions(AppSandbox PRIVATE ST_EXECUTABLE)
set_target_properties(AppSandbox PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(AppSandbox PROPERTIES ARCHIVE_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine>
		LIBRARY_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine> RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:SaturnEngine>)
