#pragma once

#include "Event.h"

namespace JLHE {

	//base class
	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		//key event is also an input  
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		//must be inherited to instantiate
		KeyEvent(int keyCode)
			:m_KeyCode(keyCode) {}

		int m_KeyCode;

	};
	
	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed Event " << m_KeyCode << " (pressed " << m_RepeatCount << " times)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};
	
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}