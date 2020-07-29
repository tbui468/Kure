#include "krpch.h"

#include "Application.h"

#include "Input.h"
#include "Kure/Log.h"

#include "Kure/Renderer/Renderer.h"
#include "Kure/Renderer/RenderCommand.h"



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

		//create vertex array (OpenGL only)		
		m_VertexArray.reset(VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		//create vertex buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_location"},
			{ShaderDataType::Float4, "a_color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//create index buffer
		std::shared_ptr<IndexBuffer> indexBuffer;
		unsigned int indices[3] = { 0 , 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//second box object to draw
		m_BoxVertexArray.reset(VertexArray::Create());

		float boxVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> boxVertexBuffer;
		boxVertexBuffer.reset(VertexBuffer::Create(boxVertices, sizeof(boxVertices)));
		BufferLayout boxLayout = {
			{ShaderDataType::Float3, "a_location"}
		};
		boxVertexBuffer->SetLayout(boxLayout);
		m_BoxVertexArray->AddVertexBuffer(boxVertexBuffer);

		std::shared_ptr<IndexBuffer> boxIndexBuffer;
		unsigned int boxIndices[6] = { 0, 1, 2, 2, 3, 0 };
		boxIndexBuffer.reset(IndexBuffer::Create(boxIndices, 6));
		m_BoxVertexArray->SetIndexBuffer(boxIndexBuffer);

		//define our shaders
		std::string vertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec4 v_Color;
		out vec3 v_Position;
	
		void main() {
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);
		}

		)";


		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	

		in vec3 v_Position;
		in vec4 v_Color;

		void main() {
			color = vec4((v_Position + 1) * 0.5, 1.0);
			color = v_Color;
		}

		)";
		//create shader
		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));


		//define our blue box shaders
		std::string blueVertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;
	
		void main() {
			gl_Position = vec4(a_Position, 1.0);
		}

		)";


		std::string blueFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	

		void main() {
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}

		)";

		m_BlueShader.reset(Shader::Create(blueVertexSrc, blueFragmentSrc));
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

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			Renderer::Submit(m_BoxVertexArray);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();


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
