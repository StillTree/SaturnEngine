#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	enum class SaturnError : U8
	{
		Ok = 0,
		CouldNotInitialize = 1,
		CouldNotOpenFile = 2,
		CouldNotCloseFile = 3,
		CouldNotWriteToFile = 4,
		CouldNotReadFromFile = 5,
		CouldNotShutDown = 6,
		Unknown = 255
	};

	constexpr U8 Failed(SaturnError err)
	{
		return static_cast<U8>(err);
	}
}
