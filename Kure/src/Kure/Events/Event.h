#pragma once

#include "Kure/Core.h"

#include <string>
#include <functional>

namespace Kure {

	//each line represents app, keyboard, mouse, etc events
	//each line has seperate header file with implementation
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//defined using a bit field b/c some event types can
	//belong to multiple categories.  Doing this allows
	//us to use a bitwise logical operators to combine
	//categories
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication   = BIT(0),
		EventCategoryInput         = BIT(1),
		EventCategoryKeyboard      = BIT(2),
		EventCategoryMouse         = BIT(3),
		EventCategoryMouseButton   = BIT(4)
	};

//Some MACROS to avoid retyping a bunch of stuff
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	//base class for events
	class KURE_API Event {
		friend class EventDispatcher; //EventDispatcher can access event members
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	//when we get event, we don't know what kind it is
	//so we create event instance and call
	//dispatch (which takes event function) on a
	//bunch of functions and only the right one
	//will activate
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e) :m_Event(e) {}
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			//handle if m_Event type is same as template of EventDispatcher instance
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event); //call function on m_Event (cast to type T)
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}