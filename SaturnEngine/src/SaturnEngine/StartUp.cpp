#include <cstdio>

#include "SaturnEngine/Core.h"
#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"

namespace SaturnEngine
{
	void SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();

	struct
	{
		ErrorManager* ErrorManager;
		LogManager* LogManager;
		FrameAllocator* FrameAllocator;
	} g_managers;

	void HugeStartUp()
	{
		//ErrorManager
		g_managers.ErrorManager = new ErrorManager;
		ErrorManager::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize ErrorManager! Something went really wrong!\nShutting down Saturn Engine...\n");

			return;
		}

		//LogManager
		g_managers.LogManager = new LogManager;
		LogManager::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");

			return;
		}

		//FrameAllocator
		g_managers.FrameAllocator = new FrameAllocator;
		FrameAllocator::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			ST_THROW_ERROR(SaturnError::CouldNotStartUp);
			ST_ERROR(L"Failed to initialize Single-Frame memory allocator! Something went really wrong!\n Shutting down Saturn Engine...");

			return;
		}

		ST_LOG(L"Saturn Engine started up successfully");

		ST_CLEAR_ERROR();
	}

	void HugeShutDown()
	{
		//FrameAllocator
		FrameAllocator::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			delete g_managers.FrameAllocator;

			ST_THROW_ERROR(SaturnError::CouldNotShutDown);
		}
		delete g_managers.FrameAllocator;

		//LogManager
		LogManager::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			delete g_managers.LogManager;

			ST_THROW_ERROR(SaturnError::CouldNotShutDown);
		}
		delete g_managers.LogManager;

		//ErrorManager
		ErrorManager::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			delete g_managers.ErrorManager;

			ST_THROW_ERROR(SaturnError::CouldNotShutDown);
		}

		ST_LOG(L"Saturn Engine shut down successfully");

		ST_CLEAR_ERROR();
	}
}