#pragma once

#include "Kure/Layer.h"

#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Events/KeyEvent.h"
#include "Kure/Events/MouseEvent.h"

namespace Kure {

	class KURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);
	private:
		//application events
		bool OnWindowResized(WindowResizedEvent& event);
		//mouse events
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		//key events
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
	private:
		float m_Time = 0.0f;
	};

}

