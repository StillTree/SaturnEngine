set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AppSandbox)

set_property(TARGET spdlog nlohmann_json PROPERTY FOLDER "Libraries")
set_property(TARGET SaturnEngine AppSandbox PROPERTY FOLDER "Core")
