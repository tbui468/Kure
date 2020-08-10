#include "krpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Kure/Renderer/RenderCommand.h"

namespace Kure {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage;

		s_Data->QuadVertexArray = VertexArray::Create();

		//test triangle
		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		unsigned int indices[6] = { 0, 1, 2 , 2, 3, 0};

		s_Data->QuadVertexArray = VertexArray::Create();
		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "vertex"}
		};
		vertexBuffer->SetLayout(layout);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 6);
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);
	}
	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->FlatColorShader->Bind();
		dynamic_cast<OpenGLShader*>(s_Data->FlatColorShader.get())->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_ViewProjMatrix"); 
		dynamic_cast<OpenGLShader*>(s_Data->FlatColorShader.get())->UploadUniformMat4(glm::mat4(1.0f), "u_Transform");
	}
	void Renderer2D::EndScene() {

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->Bind();
		dynamic_cast<OpenGLShader*>(s_Data->FlatColorShader.get())->UploadUniformFloat4(color, "u_Color");  //upload color

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data->QuadVertexArray);
	}


}
