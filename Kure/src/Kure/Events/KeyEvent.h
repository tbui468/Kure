#pragma once 
#include "Event.h"
#include <sstream>

namespace Kure {
	//abstract base class for children classes KeyPressedEvent and KeyReleasedEvent
	//constructor can only be called by the two child classes
	//GetCategoryFlags() is implemented in KeyEvent using EVENT_CLASS_CATEGORY macro
	//remaining GetName() and GetEventType() are implemented in child classes using EVENT_CLASS_TYPE macro
	class KURE_API KeyEvent :public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) 
	protected: 
		KeyEvent(int keycode) :m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class KURE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) :
			KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" <<
				m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KURE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) :
			KeyEvent(keycode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	private:
	};
}