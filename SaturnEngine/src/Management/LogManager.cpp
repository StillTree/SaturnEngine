#include "LogManager.h"

namespace SaturnEngine
{
	LogManager* LogManager::s_instance = nullptr;

	LogManager::LogManager()
	{
		assert(!s_instance && "You can't create a second instance of LogManager!");
		s_instance = this;
	}

	void LogManager::StartUp()
	{
		spdlog::set_pattern("%^[%T] %l: %v%$");
		m_logger = spdlog::stdout_color_mt("SaturnLogger");

		ST_LOG_DEBUG("LogManager initialized successfully");
	}

	void LogManager::ShutDown()
	{
		ST_LOG_DEBUG("LogManager shut down successfully");
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
