#include "Management/LogManager.h"

namespace SaturnEngine
{
	LogManager* LogManager::s_instance = nullptr;

	LogManager::LogManager()
	{
		assert(!s_instance && "You can't create a second instance of LogManager!");
		s_instance = this;
	}

	SaturnError LogManager::StartUp()
	{
		spdlog::set_pattern("%^[%T] %l: %v%$");
		m_logger = spdlog::stdout_color_mt("SaturnLogger");
		if(!m_logger)
		{
			return SaturnError::CouldNotInitialize;
		}

		ST_LOG_DEBUG("LogManager initialized successfully");

		return SaturnError::Ok;
	}

	SaturnError LogManager::ShutDown()
	{
		ST_LOG_DEBUG("LogManager shut down successfully");

		return SaturnError::Ok;
	}

	std::shared_ptr<spdlog::logger>& LogManager::Logger()
	{
		return m_logger;
	}

	LogManager* LogManager::Get()
	{
		return s_instance;
	}
}
