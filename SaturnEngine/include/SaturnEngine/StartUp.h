#pragma once

#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "Core.h"
#include "Utils/Errors.h"

namespace SaturnEngine
{
	SaturnError SATURN_API HugeStartUp();
	SaturnError SATURN_API HugeShutDown();
	void InitSaturnEngine();

	void AppStartUp();
	void AppUpdate();
	void AppShutDown();
}

inline void SaturnEngine::InitSaturnEngine()
{
	if(Failed(HugeStartUp()))
	{
		return;
	}

	AppStartUp();

	while(true)
	{
		if(Failed(FrameAllocator::Get()->Clear()))
		{
			ST_LOG_ERROR("Failed to clear FrameAllocator. Shutting down Saturn Engine...");

			return;
		}

		AppUpdate();
	}

	AppShutDown();
	if(Failed(HugeShutDown()))
	{
		return;
	}
}