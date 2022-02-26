#pragma once

namespace SaturnEngine
{
	//All the core event types.
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
	 * Every event should inherit from it and implement `GetType()` and `GetStaticType()` methods.
	 * There is a macro to make the process easier and to not forget something.
	 */
	typedef struct Event
	{
		virtual CoreEventType Type() const = 0;
	} Event;
}

#define EVENT_METHODS(eventType) \
CoreEventType Type() const override { return eventType; } \
static CoreEventType StaticType() { return eventType; }