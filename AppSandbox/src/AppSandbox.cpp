#include "SaturnEngine.h"

void SaturnEngine::AppStartUp()
{
	ST_LOG_INFO("Initializing application stuff!");
}

void SaturnEngine::AppUpdate()
{
	
}

void SaturnEngine::AppShutDown()
{
	
}

int main(char** argv, int argc)
{
	SaturnEngine::InitSaturnEngine();
}
