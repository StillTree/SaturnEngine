#include <cstdio>

#include "Core.h"
#include "../Management/LogManager.h"

namespace SaturnEngine
{
	ST_ERROR SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();
}

namespace SaturnEngine
{
	struct
	{
		LogManager* LogManager;
	} g_managers;

	ST_ERROR HugeStartUp()
	{
		g_managers.LogManager = new LogManager;
		if(LogManager::Get()->StartUp())
		{
			std::printf("Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");

			return ST_ERROR_COULD_NOT_INITIALIZE;
		}

		ST_LOG_INFO("Saturn Engine started up successfully!");

		return ST_ERROR_OK;
	}

	void HugeShutDown()
	{
		if(LogManager::Get()->ShutDown())
		{
			delete g_managers.LogManager;

			return;
		}

		ST_LOG_INFO("Saturn Engine shut down successfully!");

		delete g_managers.LogManager;
	}
}
