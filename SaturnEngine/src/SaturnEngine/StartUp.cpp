#include "Core.h"
#include "../Management/LogManager.h"

namespace SaturnEngine
{
	void SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();
}

namespace SaturnEngine
{
	struct
	{
		LogManager* LogManager;
	} g_managers;

	void HugeStartUp()
	{
		g_managers.LogManager = new LogManager;
		LogManager::Get()->StartUp();

		ST_LOG_INFO("Saturn Engine started up successfully!");
	}

	void HugeShutDown()
	{
		LogManager::Get()->ShutDown();

		ST_LOG_INFO("Saturn Engine shut down successfully!");

		delete g_managers.LogManager;
	}
}
