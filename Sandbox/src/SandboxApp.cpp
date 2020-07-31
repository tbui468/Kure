#include <Kure.h> //this is all the game engine header files



#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class GUILayer : public Kure::ImGuiLayer {

};



class ExampleLayer : public Kure::Layer {
public:
	ExampleLayer() : Layer("Example") {


		//create vertex array (OpenGL only)		
		m_VertexArray.reset(Kure::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		//create vertex buffer
		//Why are we creating memory on the heap with pointers???  Why not the stack???
		//is it because the buffers are very large?
		std::shared_ptr<Kure::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Kure::VertexBuffer::Create(vertices, sizeof(vertices))); //reset allows you to set a managed pointer to a raw pointer
		Kure::BufferLayout layout = {
			{Kure::ShaderDataType::Float3, "a_location"},
			{Kure::ShaderDataType::Float4, "a_color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//create index buffer
		std::shared_ptr<Kure::IndexBuffer> indexBuffer;
		unsigned int indices[3] = { 0 , 1, 2 };
		indexBuffer.reset(Kure::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//second box object to draw
		m_BoxVertexArray.reset(Kure::VertexArray::Create());

		float boxVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<Kure::VertexBuffer> boxVertexBuffer;
		boxVertexBuffer.reset(Kure::VertexBuffer::Create(boxVertices, sizeof(boxVertices)));
		Kure::BufferLayout boxLayout = {
			{Kure::ShaderDataType::Float3, "a_location"}
		};
		boxVertexBuffer->SetLayout(boxLayout);
		m_BoxVertexArray->AddVertexBuffer(boxVertexBuffer);

		std::shared_ptr<Kure::IndexBuffer> boxIndexBuffer;
		unsigned int boxIndices[6] = { 0, 1, 2, 2, 3, 0 };
		boxIndexBuffer.reset(Kure::IndexBuffer::Create(boxIndices, 6));
		m_BoxVertexArray->SetIndexBuffer(boxIndexBuffer);

		//define our shaders
		std::string vertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		
		uniform mat4 u_ViewProjMatrix;
		uniform mat4 u_Transform;

		out vec4 v_Color;
		out vec3 v_Position;
	
		void main() {
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);
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
		m_Shader.reset(Kure::Shader::Create(vertexSrc, fragmentSrc));


		//define our blue box shaders
		std::string blueVertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjMatrix;
		uniform mat4 u_Transform;
	
		void main() {
			gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);
		}

		)";


		std::string blueFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	

		void main() {
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}

		)";

		m_BlueShader.reset(Kure::Shader::Create(blueVertexSrc, blueFragmentSrc));

		//set up camera
		m_Camera.reset(Kure::Camera::Create(-1.6f, 1.6f, -.9f, .9f, -1.0f, 1.0f));
	}

	void OnUpdate(Kure::TimeStep ts) override {
		m_Angle += 1.0f * ts;
		//Render commands here
		Kure::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Kure::RenderCommand::Clear();

		Kure::Renderer::BeginScene(*m_Camera);

		//we need a way to upload uinforms too
		Kure::Renderer::Submit(*m_BoxVertexArray, *m_BlueShader, glm::rotate(glm::mat4(1.0f), m_Angle, { 0.0f, 0.0f, 1.0f }));

		Kure::Renderer::Submit(*m_VertexArray, *m_Shader, glm::translate(glm::mat4(1.0f), { 0.5f, 0.5f, 0.0f }));

		Kure::Renderer::EndScene();

		if (Kure::Input::IsKeyPressed(KR_KEY_A)) {
			m_CameraPos.x -= m_CameraSpeed * ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_D)) {
			m_CameraPos.x += m_CameraSpeed * ts;
		}
		if (Kure::Input::IsKeyPressed(KR_KEY_W)) {
			m_CameraPos.y += m_CameraSpeed * ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_S)) {
			m_CameraPos.y -= m_CameraSpeed * ts;
		}
		if (Kure::Input::IsKeyPressed(KR_KEY_Q)) {
			m_CameraAngle.z += m_CameraRotSpeed * ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_E)) {
			m_CameraAngle.z -= m_CameraRotSpeed * ts;
		}
		m_Camera->SetPosition(m_CameraPos);
		m_Camera->SetOrientation(m_CameraAngle);
	}

	void OnEvent(Kure::Event& event) override {
		//		KR_INFO("{0}", event);
		if (event.GetEventType() == Kure::EventType::KeyPressed)
		{
			Kure::KeyPressedEvent* e = (Kure::KeyPressedEvent*) & event;

			KR_INFO("THis key pressed: {0}", char(e->GetKeyCode()));
		}

		if (event.GetEventType() == Kure::EventType::MouseButtonPressed) {
			Kure::MouseButtonPressedEvent* e = (Kure::MouseButtonPressedEvent*) & event;
			KR_INFO("THis key pressed: {0}", char(e->GetMouseButton()));
		}
	}

	void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hi");
		ImGui::End();
	}
private:
	std::unique_ptr<Kure::VertexArray> m_VertexArray;
	std::unique_ptr<Kure::Shader> m_Shader;

	std::unique_ptr<Kure::VertexArray> m_BoxVertexArray;
	std::unique_ptr<Kure::Shader> m_BlueShader;

	std::unique_ptr<Kure::Camera> m_Camera;
	glm::vec3 m_CameraPos = glm::vec3(0.0f);
	glm::vec3 m_CameraAngle = glm::vec3(0.0f);
	float m_CameraSpeed = 1.0f;
	float m_CameraRotSpeed = 5.0f;
	float m_Angle = 0.0f;
};

//class for our app, which is a child class of Kure::Application
class Sandbox : public Kure::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};

//create new instance of our app
Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}
