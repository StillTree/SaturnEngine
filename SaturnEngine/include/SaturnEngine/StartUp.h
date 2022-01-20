#pragma once

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "Core.h"

namespace SaturnEngine
{
	void SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();
	void InitSaturnEngine();

	void AppStartUp();
	void AppUpdate();
	void AppShutDown();
}

inline void SaturnEngine::InitSaturnEngine()
{
	HugeStartUp();
	if(ST_FAILED_ERROR())
	{
		HugeShutDown();
		return;
	}

	AppStartUp();

	while(true)
	{
		FrameAllocator::Get()->Clear();
		if(ST_FAILED_ERROR())
		{
			ST_ERROR(L"Failed to clear FrameAllocator. Shutting down Saturn Engine...");

			AppStartUp();
			HugeShutDown();
			return;
		}

		AppUpdate();
	}

	AppShutDown();
	HugeShutDown();
	if(ST_FAILED_ERROR())
	{
		return;
	}
}