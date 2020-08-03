#include <Kure.h> //this is all the game engine header files
#include <glm/gtc/type_ptr.hpp>


#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class GUILayer : public Kure::ImGuiLayer {

};



class ExampleLayer : public Kure::Layer {
public:
	ExampleLayer() : Layer("Example") {


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
		m_Shader = Kure::Shader::Create(vertexSrc, fragmentSrc);


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


		//define our texture shader
		std::string textureVertexSrc = R"(
		#version 330 core 
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;

		uniform mat4 u_ViewProjMatrix;
		uniform mat4 u_Transform;
	
		void main() {
			gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);
			v_TexCoord = a_TexCoord;
		}

		)";


		std::string textureFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;	
			
		in vec2 v_TexCoord;

		uniform sampler2D u_Texture;
	
		void main() {
			color = texture(u_Texture, v_TexCoord);
		}

		)";

		m_TextureShader = Kure::Shader::Create(textureVertexSrc, textureFragmentSrc);


		m_Texture = Kure::Texture2D::Create("assets/textures/texture.png");
		m_AlphaTexture = Kure::Texture2D::Create("assets/textures/squaresTexture.png");
		dynamic_cast<Kure::OpenGLShader*>(m_TextureShader.get())->UploadUniformInt(0, "u_Texture");  //upload texture
		//set up camera
		m_Camera = Kure::Camera::Create(-1.6f, 1.6f, -.9f, .9f, -1.0f, 1.0f);
	}

	void OnUpdate(Kure::TimeStep ts) override {
//		m_Angle += 1.0f * ts;
		//Render commands here
		Kure::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Kure::RenderCommand::Clear();

		Kure::Renderer::BeginScene(*m_Camera);

		//we need a way to upload uinforms too
//		m_BlueShader->Bind();
//		dynamic_cast<Kure::OpenGLShader*>(m_BlueShader.get())->UploadUniformFloat4(glm::vec4(m_Color, 1.0f), "u_Color"); 
//		m_TextureShader->Bind();
		m_Texture->Bind();
		Kure::Renderer::Submit(*m_BoxVertexArray, glm::rotate(glm::mat4(1.0f), m_Angle, { 0.0f, 0.0f, 1.0f }), *m_TextureShader);
		m_AlphaTexture->Bind();
		Kure::Renderer::Submit(*m_BoxVertexArray, glm::rotate(glm::mat4(1.0f), m_Angle, { 0.0f, 0.0f, 1.0f }), *m_TextureShader);

		Kure::Renderer::Submit(*m_VertexArray, glm::translate(glm::mat4(1.0f), { 0.5f, 0.5f, 0.0f }), *m_Shader);

		Kure::Renderer::EndScene();

		///////////////////////////handle user inputs////////////////////

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

		if (Kure::Input::IsKeyPressed(KR_KEY_K)) {
			m_Color.g +=  ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_L)) {
			m_Color.g -=  ts;
		}

		///////////////////////////////////////////////////////////////

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
		ImGui::Begin("Color Picker");
		ImGui::Text("Hi");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_Color));
		ImGui::End();
	}
private:
	Kure::Ref<Kure::VertexArray> m_VertexArray; //triangle
	Kure::Ref<Kure::Shader> m_Shader;

	Kure::Ref<Kure::VertexArray> m_BoxVertexArray; //square
	Kure::Ref<Kure::Shader> m_BlueShader;

	Kure::Ref<Kure::Shader> m_TextureShader;
	Kure::Ref<Kure::Texture> m_Texture;
	Kure::Ref<Kure::Texture> m_AlphaTexture;

	Kure::Ref<Kure::Camera> m_Camera;
	glm::vec3 m_CameraPos = glm::vec3(0.0f);
	glm::vec3 m_CameraAngle = glm::vec3(0.0f);
	float m_CameraSpeed = 1.0f;
	float m_CameraRotSpeed = 5.0f;
	float m_Angle = 0.0f;
	glm::vec3 m_Color = glm::vec3(1.0f, 0.0f, 1.0f);
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
