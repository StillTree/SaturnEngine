#include "Management/LogSubsystem.h"

#include "Management/ErrorSubsystem.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace SaturnEngine
{
	LogSubsystem* LogSubsystem::s_instance = nullptr;

	LogSubsystem::LogSubsystem()
	{
		assert(!s_instance && L"You can't create a second instance of LogManager!");
		s_instance = this;

		spdlog::set_pattern("%^[%T] %l: %v%$");
		m_logger = spdlog::stdout_color_mt("SaturnLogger");
		if(!m_logger)
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			return;
		}

		ST_DEBUG(L"LogManager initialized successfully");

		ST_CLEAR_ERROR();
	}

	std::shared_ptr<spdlog::logger>& LogSubsystem::Logger()
	{
		return m_logger;
	}

	LogSubsystem* LogSubsystem::Get()
	{
		return s_instance;
	}
}
