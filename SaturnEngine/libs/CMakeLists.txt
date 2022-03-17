cmake_policy(SET CMP0077 NEW)

#SPDLOG
if(NOT TARGET spdlog)
	set(SPDLOG_WCHAR_SUPPORT ON)
	add_subdirectory(spdlog)
endif()
