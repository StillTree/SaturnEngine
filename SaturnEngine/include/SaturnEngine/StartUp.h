#pragma once

#include "Management/FrameAllocator.h"
#include "Core.h"
#include "Errors.h"

namespace SaturnEngine
{
	SaturnError SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();
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
			return;
		}

		AppUpdate();
	}

	AppShutDown();
	HugeShutDown();
}