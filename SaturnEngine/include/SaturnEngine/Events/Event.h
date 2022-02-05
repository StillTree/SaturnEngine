#pragma once

namespace SaturnEngine
{
	enum class CoreEventType
	{
	};

	/**
	 * Base event struct.
	 *
	 * Every event should inherit from it and implement `GetType()` and `GetStaticType()` methods.
	 * There is a macro to make the process easier and to not forget something.
	 */
	struct Event
	{
		virtual CoreEventType GetType() const = 0;
	};
}

#define EVENT_METHODS(eventType) \
EventType GetType() const override { return SaturnEngine::CoreEventType::##eventType; } \
static EventType GetStaticType() const { return SaturnEngine::CoreEventType::##eventType; }
