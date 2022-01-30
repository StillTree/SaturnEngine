#pragma once

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "Core.h"

namespace SaturnEngine
{
	bool SATURN_API HugeStartUp();
	bool SATURN_API HugeShutDown();
	void InitSaturnEngine();

	void AppStartUp();
	void AppUpdate();
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