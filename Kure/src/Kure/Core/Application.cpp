#include "krpch.h"

#include "Kure/Core/Application.h"

#include "Kure/Core/Input.h"
#include "Kure/Core/Log.h"

#include <glfw/glfw3.h>
#include "Kure/Core/TimeStep.h"

#include "Kure/Renderer/Renderer.h"




namespace Kure {


	Application* Application::s_Instance = nullptr;


	Application::Application() {
	
		KR_PROFILE_FUNCTION();


		KR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(KR_BIND_EVENT_FN(Application::OnEvent));

		m_Window->SetVSync(false);

		Renderer::Init();

		//default gui for debugging
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		KR_PROFILE_FUNCTION();
	}

	void Application::PushLayer(Layer* layer) {
		KR_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		KR_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		KR_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KR_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(KR_BIND_EVENT_FN(Application::OnWindowResize));

		//handle events from end() to begin()
		//break loop if event is handled by a layer
		for (std::vector<Layer*>::iterator iter = m_LayerStack.end(); iter != m_LayerStack.begin();) {
			(*(--iter))->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run() {
		KR_PROFILE_FUNCTION();
		while (m_Running) {
			KR_PROFILE_SCOPE("Run Loop");
			float time = (float)glfwGetTime();
			TimeStep ts = time - m_lastFrameTime;
			m_lastFrameTime = time;

			{
				KR_PROFILE_SCOPE("LayerStack OnUpdate");
				if (!m_Minimized) {
					for (Layer* layer : m_LayerStack) {
						layer->OnUpdate(ts); //pass in timestep here
					}
				}
			}

			{
				KR_PROFILE_SCOPE("Layerstack OnImGuiRender");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}


			{
				KR_PROFILE_SCOPE("Run Loop window update");
				m_Window->OnUpdate(); //event pollling and swap buffers
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(WindowResizedEvent& e) {
		KR_PROFILE_FUNCTION();
		if (e.GetHeight() == 0 || e.GetWidth() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false; //we want all layers to see this event
	}


}
