#include "SaturnEngine.h"

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

int main(int argc, char** argv)
{
	SaturnEngine::InitSaturnEngine();
}
