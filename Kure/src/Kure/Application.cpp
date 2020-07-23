#include "krpch.h"

#include "Application.h"

#include "Kure/Events/MouseEvent.h"
#include "Kure/Events/KeyEvent.h"

#include <GLFW/glfw3.h> //USING THIS TO TEST CLEARCOLOR ONLY!!!

namespace Kure {

//bind to OnEvent(Event& e) member function of 'this' instance
//place holder _1 is Event paramter we will specify at calltime
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); //OnWindowClose is only called if Event e matches type
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		KR_CORE_TRACE("{0}", e); //log events
	}

	void Application::Run() {
		//testing event system
		//only first condition should pass and print trace
		/*
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			KR_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			KR_TRACE(e);
		}*/
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	//does nothing now
	bool Application::OnWindowResize(WindowResizeEvent& e) {
		return true;
	}

}
