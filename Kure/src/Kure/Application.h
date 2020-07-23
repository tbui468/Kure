#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)
#include "Events/Event.h"
#include "Window.h"
#include "Kure/Events/ApplicationEvent.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
	private:
		//these are the functions to perform for different events
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

