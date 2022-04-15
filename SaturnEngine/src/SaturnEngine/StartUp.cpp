#include "SaturnEngine/Core.h"
#include "SaturnEngine/GlobalDataStructs.h"

namespace SaturnEngine
{
	Subsystems SATURN_API g_subsystems;
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
		//ErrorSubsystem
		g_subsystems.ErrorSubsystem = new ErrorSubsystem;
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize ErrorManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_subsystems.ErrorSubsystem;

			return false;
		}

		//LogSubsystem
		g_subsystems.LogSubsystem = new LogSubsystem;
		if(ST_FAILED_ERROR())
		{
			std::wprintf(L"Could not initialize LogManager! Something went really wrong!\nShutting down Saturn Engine...\n");
			delete g_subsystems.LogSubsystem;
			delete g_subsystems.ErrorSubsystem;

			return false;
		}

		//ConfigSubsystem
		g_subsystems.ConfigSubsystem = new ConfigSubsystem(L"saturnEngineConfig.json");
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to initialize ConfigSubsystem! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_subsystems.FrameAllocator;
			delete g_subsystems.LogSubsystem;
			delete g_subsystems.ErrorSubsystem;

			return false;
		}

		//AllocSubsystem
		g_subsystems.FrameAllocator = new AllocSubsystem;
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to initialize AllocSubsystem! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_subsystems.FrameAllocator;
			delete g_subsystems.LogSubsystem;
			delete g_subsystems.ErrorSubsystem;
			delete g_subsystems.ConfigSubsystem;

			return false;
		}

		Window::RegisterWindowClass();
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to register the Window Class! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_subsystems.FrameAllocator;
			delete g_subsystems.LogSubsystem;
			delete g_subsystems.ErrorSubsystem;

			return false;
		}
		g_globalData.MainWindow = std::make_shared<Window>(L"Application Window", 1366, 768);
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to create a Window! Something went really wrong!\n Shutting down Saturn Engine...");
			delete g_subsystems.FrameAllocator;
			delete g_subsystems.LogSubsystem;
			delete g_subsystems.ErrorSubsystem;

			return false;
		}

		ST_LOG(L"Saturn Engine started up successfully");

		ST_CLEAR_ERROR();
		return true;
	}

	bool HugeShutDown()
	{
		//AllocSubsystem
		delete g_subsystems.FrameAllocator;

		//ConfigSubsystem
		delete g_subsystems.ConfigSubsystem;

		//LogSubsystem
		delete g_subsystems.LogSubsystem;

		//ErrorSubsystem
		delete g_subsystems.ErrorSubsystem;

		std::wprintf(L"Saturn Engine shut down successfully\n");

		ST_CLEAR_ERROR();
		return true;
	}
}
