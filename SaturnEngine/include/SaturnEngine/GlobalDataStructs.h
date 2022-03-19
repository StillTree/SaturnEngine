#pragma once

#include "Management/ErrorSubsystem.h"
#include "Management/LogSubsystem.h"
#include "Management/AllocSubsystem.h"
#include "SaturnEngine/Window.h"

namespace SaturnEngine
{
	//Structure containing all the managers present in the engine.
	typedef struct Managers
	{
		ErrorSubsystem* ErrorManager = nullptr;
		LogSubsystem* LogManager = nullptr;
		AllocSubsystem* FrameAllocator = nullptr;
	} Managers;

	//Structure containing all the data required for the application.
	typedef struct GlobalData
	{
		std::shared_ptr<Window> MainWindow = nullptr;
	} GlobalData;
}
