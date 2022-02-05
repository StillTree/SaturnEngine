#pragma once

namespace SaturnEngine
{
	enum class EventType
	{
		
	};

	struct Event
	{
		virtual EventType GetType() const = 0;
 	};
}
