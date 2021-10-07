#pragma once

#include <memory>
#include <cassert>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/spdlog.h"
#include "../SaturnEngine/Core.h"
#include "../SaturnEngine/Errors.h"

namespace SaturnEngine
{
	class SATURN_API LogManager
	{
	public:
		LogManager();
		~LogManager() = default;

		ST_ERROR StartUp();
		ST_ERROR ShutDown();
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

#define ST_LOG_INFO(...) SaturnEngine::LogManager::Get()->Logger()->info(__VA_ARGS__)
#ifdef _DEBUG
#define ST_LOG_DEBUG(...) SaturnEngine::LogManager::Get()->Logger()->info(__VA_ARGS__)
#else
#define SAT_LOG_DEBUG(...)
#endif
#define ST_LOG_WARN(...) SaturnEngine::LogManager::Get()->Logger()->warn(__VA_ARGS__)
#define ST_LOG_ERROR(...) SaturnEngine::LogManager::Get()->Logger()->error(__VA_ARGS__)
