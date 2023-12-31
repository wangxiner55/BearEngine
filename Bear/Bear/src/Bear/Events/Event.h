#pragma once
#include "../Core.h"

#include <string>
#include <functional>


namespace BEngine
{

	// immediatelt get dispatched and dealt with right 
	// no delay or queue or list eg... 

	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFoucus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled
	};

	enum EventCategoty
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual const EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override{return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }



	class BEAR_API Event
	{
		friend class EventDispatcher;

	public:

		virtual const EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline const bool IsInCategory(const EventCategoty& category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		
	public:

		template<typename T>
		using EventFn = std::function<bool(T&)>;

		EventDispatcher(Event& event)
			:m_Event(event){}

		template<typename T>
		
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
