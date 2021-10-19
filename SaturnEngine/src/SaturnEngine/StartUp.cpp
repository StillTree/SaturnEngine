#include <cstdio>

#include "Core.h"
#include "../Management/LogManager.h"

namespace SaturnEngine
{
	SaturnError SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();

	struct
	{
		LogManager* LogManager;
	} g_managers;

	SaturnError HugeStartUp()
	{
		g_managers.LogManager = new LogManager;
		if(Failed(LogManager::Get()->StartUp()))
		{
			std::printf("Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");

			return SaturnError::CouldNotInitialize;
		}

		ST_LOG_INFO("Saturn Engine started up successfully!");

		return SaturnError::Ok;
	}

	void HugeShutDown()
	{
		if(Failed(LogManager::Get()->ShutDown()))
		{
			delete g_managers.LogManager;

			return;
		}
		delete g_managers.LogManager;

		ST_LOG_INFO("Saturn Engine shut down successfully!");
	}
}