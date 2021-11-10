#include <cstdio>

#include "SaturnEngine/Core.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"

namespace SaturnEngine
{
	SaturnError SATURN_API HugeStartUp();
	SaturnError SATURN_API HugeShutDown();

	struct
	{
		LogManager* LogManager;
		FrameAllocator* FrameAllocator;
	} g_managers;

	SaturnError HugeStartUp()
	{
		//LogManager
		g_managers.LogManager = new LogManager;
		if(Failed(LogManager::Get()->StartUp()))
		{
			std::printf("Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");

			return SaturnError::CouldNotInitialize;
		}

		//FrameAllocator
		g_managers.FrameAllocator = new FrameAllocator;
		if(Failed(FrameAllocator::Get()->StartUp()))
		{
			ST_LOG_ERROR("Failed to initialize Single-Frame memory allocator! Something went really wrong!\n Shutting down Saturn Engine...");

			return SaturnError::CouldNotInitialize;
		}

		ST_LOG_INFO("Saturn Engine started up successfully");

		return SaturnError::Ok;
	}

	SaturnError HugeShutDown()
	{
		//FrameAllocator
		if(Failed(FrameAllocator::Get()->ShutDown()))
		{
			delete g_managers.FrameAllocator;

			return SaturnError::CouldNotShutDown;
		}
		delete g_managers.FrameAllocator;

		//LogManager
		if(Failed(LogManager::Get()->ShutDown()))
		{
			delete g_managers.LogManager;

			return SaturnError::CouldNotShutDown;
		}
		delete g_managers.LogManager;

		ST_LOG_INFO("Saturn Engine shut down successfully");

		return SaturnError::Ok;
	}
}