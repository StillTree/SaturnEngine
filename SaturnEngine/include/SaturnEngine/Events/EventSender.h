#pragma once

#include "Event.h"

//The whole event thing is based `Niko Savas`'s implementation in his `Nomad Game Engine`

namespace SaturnEngine
{
	/**
	 * Base class for storing event functions.
	 *
	 * Inheritance allows to then have two separate child classes one taking a standalone function
	 * and another taking a member function.
	 */
	class EventFunctionBase
	{
	public:
		inline void Call(Event& e)
		{
			Execute(e);
		}

	protected:
		virtual void Execute(Event& e) = 0;
	};

	/**
	 * Child class of EventFunctionBase, only taking a standalone function.
	 *
	 * @tparam T event class type which must contain a GetStaticType() method
	 */
	template<typename T>
	class Function : public EventFunctionBase
	{
	public:
		explicit Function(void (*eFn)(const T&)) : m_function(eFn)
		{
		}

		void Execute(Event& e) override
		{
			m_function(dynamic_cast<T&>(e));
		}

	private:
		void (*m_function)(const T&);
	};

	/**
	 * Handles and sends events to subscribers.
	 *
	 * Making it a class allows the engine user to then use the event system on his own and create custom events.
	 */
	class EventSender
	{
	public:
		EventSender() = default;

		/**
		 * Adds a method as an event listener.
		 *
		 * @tparam T event class type which must contain a GetStaticType() method
		 * @param eventFunction function handling the event
		 */
		template<typename T>
		void Subscribe(void (*eventFunction)(const T&))
		{
			std::vector<EventFunctionBase*>& functions = m_subscribers[T::StaticType()];

			functions.push_back(new Function<T>(eventFunction));
		}

		/**
		 * Sends an event to subscribers listening to it.
		 *
		 * @tparam T event class type which must contain a GetStaticType() method
		 * @param e the event itself
		 */
		template<typename T>
		void Invoke(T& e)
		{
			std::vector<EventFunctionBase*>& functions = m_subscribers[T::StaticType()];

			for(auto* handler : functions)
			{
				handler->Call(e);
			}
		}

	private:
		std::map<CoreEventType, std::vector<EventFunctionBase*>> m_subscribers;
	};
}
