#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)

#include "Window.h"
#include "Kure/LayerStack.h"
#include "Kure/ImGui/ImGuiLayer.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_lastFrameTime = 0.0f;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

