#include "krpch.h"

#include "Application.h"

#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Events/MouseEvent.h"
#include "Kure/Events/KeyEvent.h"
#include "Kure/Log.h"

namespace Kure {
	Application::Application() {
	}

	Application::~Application() {
	}

	void Application::Run() {
		//testing event system
		//only first condition should pass and print trace
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			KR_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			KR_TRACE(e);
		}
		while (true);
	}

}
