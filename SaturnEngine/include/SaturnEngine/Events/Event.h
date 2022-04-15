#pragma once

namespace SaturnEngine
{
	//Core event types.
	enum class CoreEventType : U8
	{
		MouseMove = 0,
		MouseScroll = 1,
		LeftMouseButtonUp = 2,
		LeftMouseButtonDown = 3,
		RightMouseButtonUp = 4,
		RightMouseButtonDown = 5,
		KeyUp = 6,
		KeyDown = 7
	};

	/**
	 * Base event struct.
	 *
	 * Every event should inherit from it and create `Type` and `StaticType` fields.
	 * There is a macro to make the process easier and also faster.
	 */
	typedef struct Event { } Event;
}

#define EVENT_METHODS(eventType) \
CoreEventType Type = eventType; \
static constexpr CoreEventType StaticType = eventType;
