#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)

#include "Window.h"
#include "Kure/LayerStack.h"
#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Renderer/Shader.h"
#include "Kure/Renderer/Buffer.h"
#include "Kure/Renderer/VertexArray.h"


#include "Kure/ImGui/ImGuiLayer.h"

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
		//this is one of the events
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_BoxVertexArray;
		std::shared_ptr<Shader> m_BlueShader;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

