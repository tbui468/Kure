#include "krpch.h"

#include "Application.h"

#include "Input.h"
#include "Kure/Log.h"

#include <glfw/glfw3.h>
#include "Kure/Core/TimeStep.h"




namespace Kure {


	Application* Application::s_Instance = nullptr;


	Application::Application() {
		KR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(KR_BIND_EVENT_FN(Application::OnEvent));

		m_Window->SetVSync(true);

		//default gui for debugging
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KR_BIND_EVENT_FN(Application::OnWindowClose));

		//handle events from end() to begin()
		//break loop if event is handled by a layer
		for (std::vector<Layer*>::iterator iter = m_LayerStack.end(); iter != m_LayerStack.begin();) {
			(*(--iter))->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run() {

		while (m_Running) {
			float time = (float)glfwGetTime();
			TimeStep ts = time - m_lastFrameTime;
			m_lastFrameTime = time;

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(ts); //pass in timestep here
			}


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();



			m_Window->OnUpdate(); //event pollling and swap buffers
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}


}
