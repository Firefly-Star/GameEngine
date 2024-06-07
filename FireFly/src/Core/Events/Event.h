#pragma once


#include "../Core.h"
#include "spdlog/spdlog.h"

namespace FireFly
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped, 
		MousePressed, MouseReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
	{
		None = 0,
		EventApplication = BIT(0),
		EventWindow = BIT(1),
		EventKey = BIT(2),
		EventMouse = BIT(3),
		EventInput = BIT(4)
	};

#define EVENT_TYPE_FUNCTION(type)\
	static EventType GetStaticType() { return EventType::##type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }

#define EVENT_CATEGORY_FUNCTION(category)\
	virtual int GetEventCategory() const override { return (category); }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() {}
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return (int)category & GetEventCategory();
		}

		inline bool IsHandled() const { return m_Handled; }
	protected:
		bool m_Handled = false;
	};
	

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e){}


		template<typename T>
		bool EventDispatch(std::function<bool(T&)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*((T*)(&m_Event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const FireFly::Event& e)
	{
		return os << e.ToString();
	}
}
