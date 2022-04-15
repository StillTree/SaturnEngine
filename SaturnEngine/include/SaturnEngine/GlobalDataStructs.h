#pragma once

#include "Management/ErrorSubsystem.h"
#include "Management/LogSubsystem.h"
#include "Management/AllocSubsystem.h"
#include "Management/ConfigSubsystem.h"
#include "SaturnEngine/Window.h"

namespace SaturnEngine
{
	//Structure containing all the subsystems present in the engine.
	typedef struct Subsystems
	{
		ErrorSubsystem* ErrorSubsystem = nullptr;
		LogSubsystem* LogSubsystem = nullptr;
		AllocSubsystem* FrameAllocator = nullptr;
		ConfigSubsystem* ConfigSubsystem = nullptr;
	} Managers;

	//Structure containing all the data required for the application.
	typedef struct GlobalData
	{
		std::shared_ptr<Window> MainWindow = nullptr;
	} GlobalData;
}
