#include "SaturnEngine.h"

void SaturnEngine::AppStartUp()
{
	ST_LOG(L"Initializing application stuff");
}

void SaturnEngine::AppUpdate()
{

}

void SaturnEngine::AppShutDown()
{

}

int main(int argc, char** argv)
{
	SaturnEngine::InitSaturnEngine();
}
