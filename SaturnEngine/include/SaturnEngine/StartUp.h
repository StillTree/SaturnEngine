#pragma once

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "Core.h"
#include "Utils/Errors.h"

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
	if(Failed(ST_LAST_ERROR()))
	{
		return;
	}

	AppStartUp();

	while(true)
	{
		FrameAllocator::Get()->Clear();
		if(Failed(ST_LAST_ERROR()))
		{
			ST_ERROR(L"Failed to clear FrameAllocator. Shutting down Saturn Engine...");

			return;
		}

		AppUpdate();
	}

	AppShutDown();
	HugeShutDown();
	if(Failed(ST_LAST_ERROR()))
	{
		return;
	}
}