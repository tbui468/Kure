#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)

#include "Window.h"
#include "Kure/LayerStack.h"
#include "Kure/Events/Event.h"
#include "Kure/Events/ApplicationEvent.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		//these are the functions to perform for different events
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

