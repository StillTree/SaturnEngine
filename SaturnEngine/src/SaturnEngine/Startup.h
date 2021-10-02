#pragma once

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
	AppStartUp();

	while(true)
	{
		AppUpdate();
	}

	AppShutDown();
	HugeShutDown();
}
