#pragma once

#include "Core.h"
#include "SaturnEngine/GlobalDataStructs.h"

namespace SaturnEngine
{
	extern Managers SATURN_API g_managers;
	extern GlobalData SATURN_API g_globalData;

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
	// Initializes the while engine including the app itself. Should only be used once, in the `main()` function.
	void InitSaturnEngine();

	// Called after starting up the core engine.
	void AppStartUp();
	// Called every frame.
	void AppUpdate();
	// Called before shutting down the core engine.
	void AppShutDown();

	inline void InitSaturnEngine()
	{
		if(!HugeStartUp())
		{
			std::wprintf(L"Could not start up Saturn Engine, shutting down...\n");
			return;
		}
		AppStartUp();
		ST_CLEAR_ERROR();

		MSG msg = {};
		while(msg.message != WM_QUIT)
		{
			if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				FrameAllocator::Get()->Clear();
				if(ST_FAILED_ERROR())
				{
					ST_ERROR(L"Failed to clear FrameAllocator. Shutting down Saturn Engine...");

					AppShutDown();
					ST_CLEAR_ERROR();
					HugeShutDown();
					return;
				}

				AppUpdate();
				ST_CLEAR_ERROR();
			}
		}

		AppShutDown();
		ST_CLEAR_ERROR();
		HugeShutDown();
	}
}

#define MAIN_WINDOW SaturnEngine::g_globalData.MainWindow
