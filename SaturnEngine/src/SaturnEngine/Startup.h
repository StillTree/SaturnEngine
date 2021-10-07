#pragma once

#include "Core.h"
#include "Errors.h"

namespace SaturnEngine
{
	ST_ERROR SATURN_API HugeStartUp();
	void SATURN_API HugeShutDown();
	void InitSaturnEngine();

	void AppStartUp();
	void AppUpdate();
	void AppShutDown();
}

inline void SaturnEngine::InitSaturnEngine()
{
	if(HugeStartUp())
	{
		return;
	}

	AppStartUp();

	while(true)
	{
		AppUpdate();
	}

	AppShutDown();
	HugeShutDown();
}
