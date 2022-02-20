#pragma once

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"
#include "Management/FrameAllocator.h"
#include "SaturnEngine/Window.h"

namespace SaturnEngine
{
	//Structure containing all the managers present in the engine.
	typedef struct Managers
	{
		ErrorManager* ErrorManager = nullptr;
		LogManager* LogManager = nullptr;
		FrameAllocator* FrameAllocator = nullptr;
	} Managers;

	//Structure containing all the data required for the application.
	typedef struct GlobalData
	{
		std::shared_ptr<Window> MainWindow = nullptr;
	} GlobalData;
}
