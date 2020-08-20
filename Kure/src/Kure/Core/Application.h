#pragma once

#include "Kure/Core/Core.h" //need this for KURE_API (which exports the class)

#include "Kure/Core/Window.h"
#include "Kure/Core/LayerStack.h"
#include "Kure/ImGui/ImGuiLayer.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application(const std::string& name = "Kure App");
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void Run();
		void Close();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_lastFrameTime = 0.0f;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

