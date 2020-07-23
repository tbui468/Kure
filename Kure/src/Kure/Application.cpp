#include "krpch.h"

#include "Application.h"

#include <glad/glad.h>

namespace Kure {

//bind to OnEvent(Event& e) member function of 'this' instance
//place holder _1 is Event paramter we will specify at calltime
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); //OnWindowClose is only called if Event e matches type
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//KR_CORE_TRACE("{0}", e); //log events

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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//update layers from begin() to end()
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	//does nothing now
	bool Application::OnWindowResize(WindowResizeEvent& e) {
		return true;
	}

}
