#include "krpch.h"

#include "Application.h"

#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Events/MouseEvent.h"
#include "Kure/Events/KeyEvent.h"

#include <GLFW/glfw3.h> //USING THIS TO TEST CLEARCOLOR ONLY!!!

namespace Kure {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
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

}
