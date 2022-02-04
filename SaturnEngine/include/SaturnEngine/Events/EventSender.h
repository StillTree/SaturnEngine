#pragma once

#include <map>
#include <vector>

#include "Event.h"

namespace SaturnEngine
{
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

	class EventSender
	{
	public:
		EventSender() = default;

		template<typename T>
		void Subscribe(void (*eventFunction)(const T&))
		{
			std::vector<EventFunctionBase*>& functions = m_subscribers[T::GetStaticType()];

			functions.push_back(new Function<T>(eventFunction));
		}

		template<typename T>
		void Invoke(T& e)
		{
			std::vector<EventFunctionBase*>& functions = m_subscribers[T::GetStaticType()];

			for(auto* handler : functions)
			{
				handler->Call(e);
			}
		}

	private:
		std::map<EventType, std::vector<EventFunctionBase*>> m_subscribers;
	};
}
