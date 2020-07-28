#include "krpch.h"

#include "Application.h"

#include "Input.h"
#include "Kure/Log.h"

#include <glad/glad.h>


namespace Kure {

//bind to OnEvent(Event& e) member function of 'this' instance
//place holder _1 is Event paramter we will specify at calltime

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		KR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(KR_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//create and bind vertex array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//create and bind vertex buffer
		//define data, and load into GPU
		//glGenBuffers(1, &m_VertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);


		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		//define vertex attrib
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//create and bind index buffer
		//define data, and load into GPU
		//glGenBuffers(1, &m_IndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0 , 1, 2 };
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		//define our shaders
		std::string vertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;

		out vec3 v_Position;
	
		void main() {
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}

		)";


		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	

		in vec3 v_Position;

		void main() {
			color = vec4((v_Position + 1) * 0.5, 1.0);
		}

		)";
		//shader
		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray); //redundant, but for clarity
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			//update layers from begin() to end()
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
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
