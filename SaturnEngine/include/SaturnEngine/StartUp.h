#pragma once

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "Core.h"

namespace SaturnEngine
{
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

		while(true)
		{
			FrameAllocator::Get()->Clear();
			if(ST_FAILED_ERROR())
			{
				ST_ERROR(L"Failed to clear FrameAllocator. Shutting down Saturn Engine...");

				AppShutDown();
				HugeShutDown();
				return;
			}

			AppUpdate();
			ST_CLEAR_ERROR();
		}

		AppShutDown();
		ST_CLEAR_ERROR();
		HugeShutDown();
	}
}