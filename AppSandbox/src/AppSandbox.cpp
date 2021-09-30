#include "SaturnEngine.h"

int main(char** argv, int argc)
{
	SaturnEngine::BigStartUp();
	
	ST_LOG_INFO("Initalizing application stuff!");

	SaturnEngine::BigShutDown();
}
