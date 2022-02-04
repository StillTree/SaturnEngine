#pragma once

namespace SaturnEngine
{
	enum class EventType
	{
		JoeEvent
	};

	struct Event
	{
		virtual EventType GetType() const = 0;
 	};
}
