#pragma once


#include "Event.h"

namespace FireFly
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode) : m_Keycode(keycode){}
		virtual ~KeyEvent(){}
		int m_Keycode;
	public:
		inline int GetKeyCode() const { return m_Keycode; }
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventKey | (int)EventCategory::EventInput)
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatcount) : KeyEvent(keycode), m_RepeatCount(repeatcount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << m_Keycode << " with " << m_RepeatCount << " times repeated.";
			return ss.str();
		}
		EVENT_TYPE_FUNCTION(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << m_Keycode;
			return ss.str();
		}

		EVENT_TYPE_FUNCTION(KeyReleased)
	};

	class KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(unsigned int character) : m_Character(character) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Keytyped: " << m_Character;
			return ss.str();
		}
		inline unsigned int GetChar() const { return m_Character; }
		EVENT_TYPE_FUNCTION(KeyTyped)
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventKey | (int)EventCategory::EventInput)

	private:
		unsigned int m_Character;
	};
}