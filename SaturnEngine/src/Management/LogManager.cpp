#include "Management/LogManager.h"

#include "Management/ErrorManager.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace SaturnEngine
{
	LogManager* LogManager::s_instance = nullptr;

	LogManager::LogManager()
	{
		assert(!s_instance && L"You can't create a second instance of LogManager!");
		s_instance = this;
	}

	void LogManager::StartUp()
	{
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

	void LogManager::ShutDown()
	{
		std::wprintf(L"LogManager shut down successfully");
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
