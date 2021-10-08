#pragma once

#include <cstdint>

namespace SaturnEngine
{
	enum class SaturnError : int8_t
	{
		Ok,
		CouldNotInitialize = 1,
		Unknown = -1
	};

	constexpr int8_t Failed(SaturnError err)
	{
		return static_cast<int8_t>(err);
	}
}
