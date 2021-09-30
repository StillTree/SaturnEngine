#include "StartUp.h"

#include "../Management/LogManager.h"

namespace SaturnEngine
{
	struct
	{
		LogManager* LogManager;
	} g_managers;

	void BigStartUp()
	{
		g_managers.LogManager = new LogManager;
		LogManager::Get()->StartUp();

		ST_LOG_INFO("Saturn Engine started up successfully!");
	}

	void BigShutDown()
	{
		LogManager::Get()->ShutDown();

		ST_LOG_INFO("Saturn Engine shut down successfully!");

		delete g_managers.LogManager;
	}
}
