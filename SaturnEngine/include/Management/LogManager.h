#pragma once

#include <memory>

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT

#include "spdlog/spdlog.h"
#include "Utils/Errors.h"

namespace SaturnEngine
{
	class SATURN_API LogManager
	{
	public:
		LogManager();
		~LogManager() = default;

		void StartUp();
		void ShutDown();
		std::shared_ptr<spdlog::logger>& Logger();
		static LogManager* Get();
	
		LogManager(const LogManager& other) = default;
		LogManager(LogManager&& other) = default;

		LogManager& operator=(const LogManager& other) = default;
		LogManager& operator=(LogManager&& other) = default;

	private:
		static LogManager* s_instance;

		std::shared_ptr<spdlog::logger> m_logger;
	};
}

#define ST_LOG(...) SaturnEngine::LogManager::Get()->Logger()->info(__VA_ARGS__)
#ifdef ST_BUILD_DEBUG
#define ST_DEBUG(...) SaturnEngine::LogManager::Get()->Logger()->info(__VA_ARGS__)
#else
#define ST_DEBUG(...)
#endif
#define ST_WARN(...) SaturnEngine::LogManager::Get()->Logger()->warn(__VA_ARGS__)
#define ST_ERROR(...) SaturnEngine::LogManager::Get()->Logger()->error(__VA_ARGS__)
