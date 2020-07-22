#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)
#include "Events/Event.h"
#include "Window.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

