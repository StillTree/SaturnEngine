set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_property(TARGET spdlog PROPERTY FOLDER "Libraries")
if(ST_BUILD_EXAMPLES)
	set_property(TARGET EmptyApp PROPERTY FOLDER "Examples")
endif()
