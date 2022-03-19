#include "SaturnEngine/Core.h"
#include "SaturnEngine/GlobalDataStructs.h"

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
		g_managers.ErrorManager = new ErrorSubsystem;
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize ErrorManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_managers.ErrorManager;

			return false;
		}

		//LogManager
		g_managers.LogManager = new LogSubsystem;
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}

		//FrameAllocator
		g_managers.FrameAllocator = new AllocSubsystem;
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to initialize FrameAllocator! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_managers.FrameAllocator;
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}

		Window::RegisterWindowClass();
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to register the Window Class! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_managers.FrameAllocator;
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}
		g_globalData.MainWindow = std::make_shared<Window>(L"Application Window", 1366, 768);
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to create a Window! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_managers.FrameAllocator;
			delete g_managers.LogManager;
			delete g_managers.ErrorManager;

			return false;
		}

		ST_LOG(L"Saturn Engine started up successfully");

		ST_CLEAR_ERROR();
		return true;
	}

	bool HugeShutDown()
	{
		//FrameAllocator
		delete g_managers.FrameAllocator;

		//LogManager
		delete g_managers.LogManager;

		//ErrorManager
		delete g_managers.ErrorManager;

		std::wprintf(L"Saturn Engine shut down successfully\n");

		ST_CLEAR_ERROR();
		return true;
	}
}
