#include <Kure.h> //this is all the game engine header files
#include <glm/gtc/type_ptr.hpp>


#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.h"


#include "Kure/Core/EntryPoint.h"



class ExampleLayer : public Kure::Layer {
public:
	ExampleLayer() : Layer("Example") {


		m_CameraController.reset(new Kure::OrthographicCameraController(1280.0f / 720.0f, true));


		//create vertex array (OpenGL only)		
		m_VertexArray = Kure::VertexArray::Create();


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		//create vertex buffer
		//Why are we creating memory on the heap with pointers???  Why not the stack???
		//is it because the buffers are very large?
		Kure::Ref<Kure::VertexBuffer> vertexBuffer;
		vertexBuffer = Kure::VertexBuffer::Create(vertices, sizeof(vertices));
		Kure::BufferLayout layout = {
			{Kure::ShaderDataType::Float3, "a_location"},
			{Kure::ShaderDataType::Float4, "a_color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//create index buffer
		Kure::Ref<Kure::IndexBuffer> indexBuffer;
		unsigned int indices[3] = { 0 , 1, 2 };
		indexBuffer = Kure::IndexBuffer::Create(indices, 3);
		m_VertexArray->SetIndexBuffer(indexBuffer);




		//second box object to draw
		m_BoxVertexArray = Kure::VertexArray::Create();

		float boxVertices[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f, 
			0.75f, 0.75f, 0.0f, 1.0f, 1.0f, 
			-0.75f, 0.75f, 0.0f, 0.0f, 1.0f
		};

		Kure::Ref<Kure::VertexBuffer> boxVertexBuffer;
		boxVertexBuffer = Kure::VertexBuffer::Create(boxVertices, sizeof(boxVertices));
		Kure::BufferLayout boxLayout = {
			{Kure::ShaderDataType::Float3, "a_location"},
			{Kure::ShaderDataType::Float2, "a_texCoord"}
		};
		boxVertexBuffer->SetLayout(boxLayout);
		m_BoxVertexArray->AddVertexBuffer(boxVertexBuffer);

		Kure::Ref<Kure::IndexBuffer> boxIndexBuffer;
		unsigned int boxIndices[6] = { 0, 1, 2, 2, 3, 0 };
		boxIndexBuffer = Kure::IndexBuffer::Create(boxIndices, 6);
		m_BoxVertexArray->SetIndexBuffer(boxIndexBuffer);

		//triangle shader
		std::string vertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		
		uniform mat4 u_ViewProjMatrix;
		uniform mat4 u_Transform;

		out vec4 v_Color;
	
		void main() {
			v_Color = a_Color;
			gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);
		}

		)";


		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	

		in vec4 v_Color;


		void main() {
			color = v_Color;
		}

		)";
		//create shader
		m_Shader = Kure::Shader::Create("texturename", vertexSrc, fragmentSrc);


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
		uniform vec4 u_Color;

		void main() {
			color = vec4(0.2, 0.3, 0.8, 1.0);
			color = u_Color;
		}

		)";

//		m_BlueShader.reset(Kure::Shader::Create(blueVertexSrc, blueFragmentSrc));



		m_ShaderLibrary.Load("TextureShader", "assets/shaders/Texture.glsl");

		auto textureShader = m_ShaderLibrary.Get("TextureShader");

		m_Texture = Kure::Texture2D::Create("assets/textures/texture.png");
		m_AlphaTexture = Kure::Texture2D::Create("assets/textures/squaresTexture.png");
		dynamic_cast<Kure::OpenGLShader*>(textureShader.get())->UploadUniformInt(0, "u_Texture");  //upload texture
		//set up camera
	}

	void OnUpdate(Kure::TimeStep ts) override {

		m_CameraController->OnUpdate(ts);

		//Render commands here
		Kure::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Kure::RenderCommand::Clear();

		Kure::Renderer::BeginScene(m_CameraController->GetCamera());

		auto textureShader = m_ShaderLibrary.Get("TextureShader");

		m_Texture->Bind();
		Kure::Renderer::Submit(*m_BoxVertexArray, glm::rotate(glm::mat4(1.0f), m_Angle, { 0.0f, 0.0f, 1.0f }), *textureShader);
		m_AlphaTexture->Bind();
		Kure::Renderer::Submit(*m_BoxVertexArray, glm::rotate(glm::mat4(1.0f), m_Angle, { 0.0f, 0.0f, 1.0f }), *textureShader);

		Kure::Renderer::Submit(*m_VertexArray, glm::translate(glm::mat4(1.0f), { 0.5f, 0.5f, 0.0f }), *m_Shader);

		Kure::Renderer::EndScene();

	}

	void OnEvent(Kure::Event& event) override {

		m_CameraController->OnEvent(event);

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
		ImGui::Begin("Color Picker");
		ImGui::Text("Hi");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_Color));
		ImGui::End();
	}
private:
	Kure::ShaderLibrary m_ShaderLibrary;
	Kure::Ref<Kure::VertexArray> m_VertexArray; //triangle
	Kure::Ref<Kure::Shader> m_Shader;

	Kure::Ref<Kure::VertexArray> m_BoxVertexArray; //square
	Kure::Ref<Kure::Shader> m_BlueShader;

	//Kure::Ref<Kure::Shader> m_TextureShader;
	Kure::Ref<Kure::Texture> m_Texture;
	Kure::Ref<Kure::Texture> m_AlphaTexture;

	float m_Angle = 0.0f; //angle of rotatation for shapes (NOT CAMERA)

	Kure::Ref<Kure::OrthographicCameraController> m_CameraController;
	glm::vec3 m_Color = glm::vec3(1.0f, 0.0f, 1.0f);
};

//class for our app, which is a child class of Kure::Application
class Sandbox : public Kure::Application
{
public:
	Sandbox() {
//		PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {

	}
};

//create new instance of our app
Kure::Application* Kure::CreateApplication() {
	return new Sandbox();
}
