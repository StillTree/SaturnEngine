#include "SaturnEngine/Core.h"
#include "SaturnEngine/GlobalDataStructs.h"

#include <cstdio>

namespace SaturnEngine
{
	Managers SATURN_API g_managers;
	GlobalData SATURN_API g_globalData;

	/**
	 * Starts up the core engine including the managers.
	 *
	 * @return if starting up went successfully
	 */
	bool SATURN_API HugeStartUp();
	/**
	 * Shuts down the core engine including the managers.
	 *
	 * @return if shutting down went successfully
	 */
	bool SATURN_API HugeShutDown();

	bool HugeStartUp()
	{
		//ErrorManager
		g_managers.ErrorManager = new ErrorManager;
		ErrorManager::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize ErrorManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_managers.ErrorManager;

			return false;
		}

		//LogManager
		g_managers.LogManager = new LogManager;
		LogManager::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}

		//FrameAllocator
		g_managers.FrameAllocator = new FrameAllocator;
		FrameAllocator::Get()->StartUp();
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to initialize Single-Frame memory allocator! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_managers.FrameAllocator;
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}

		Window::RegisterWindowClass();
		g_globalData.MainWindow = new Window(L"Application Window", 1366, 768);

		ST_LOG(L"Saturn Engine started up successfully");

		ST_CLEAR_ERROR();
		return true;
	}

	bool HugeShutDown()
	{
		//FrameAllocator
		FrameAllocator::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			ST_THROW_ERROR(SaturnError::CouldNotShutDown);
		}
		delete g_managers.FrameAllocator;

		//LogManager
		LogManager::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"An error occurred while shutting down!");
		}
		delete g_managers.LogManager;

		//ErrorManager
		ErrorManager::Get()->ShutDown();
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"An error occurred while shutting down!");
		}
		delete g_managers.ErrorManager;

		std::wprintf(L"Saturn Engine shut down successfully\n");

		return true;
	}
}
