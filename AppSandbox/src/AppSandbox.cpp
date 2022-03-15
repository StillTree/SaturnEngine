#include "SaturnEngine.h"

//TODO: RapidJSON
//TODO: Refactor managers

namespace SaturnEngine
{
	void AppStartUp()
	{
		ST_LOG(L"Initializing application stuff");
	}

	void AppUpdate()
	{

	}

	void AppShutDown()
	{

	}
}

int main(int, char**)
{
	SaturnEngine::InitSaturnEngine();
}
