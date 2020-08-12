#include "krpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Kure/Renderer/RenderCommand.h"


#include <glm/gtc/type_ptr.hpp> 

namespace Kure {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> CombinedShader; //combined flat color shader and texture shader
		Ref<Texture> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage;

		s_Data->QuadVertexArray = VertexArray::Create();

		//test quad
		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indices[6] = { 0, 1, 2 , 2, 3, 0};

		s_Data->QuadVertexArray = VertexArray::Create();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "vertex"},
			{ShaderDataType::Float2, "texCoord"}
		};
		vertexBuffer->SetLayout(layout);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 6);
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		//create white texture
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t data = 0xffffffff;
		s_Data->WhiteTexture->SetData(&data, sizeof(uint32_t));

		//combined flat color and texture shader
		s_Data->CombinedShader = Shader::Create("assets/shaders/Combined.glsl");
		s_Data->CombinedShader->Bind();
		s_Data->CombinedShader->SetInt(0, "u_Texture");
	}
	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->CombinedShader->Bind();
		s_Data->CombinedShader->SetMat4(camera.GetViewProjectionMatrix(), "u_ViewProjMatrix");
	}
	void Renderer2D::EndScene() {

	}


	//axis aligned quads
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->CombinedShader->SetFloat4(color, "u_Color");  //upload color
		s_Data->CombinedShader->SetFloat(1.0f, "u_TexScale");

		s_Data->WhiteTexture->Bind(0); //bind a solid white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		s_Data->CombinedShader->SetMat4(transform, "u_Transform");

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data->QuadVertexArray);
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, texScale, tint);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		s_Data->CombinedShader->SetFloat4(tint, "u_Color");  
		s_Data->CombinedShader->SetFloat(texScale, "u_TexScale");

		texture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->CombinedShader->SetMat4(transform, "u_Transform");

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data->QuadVertexArray);
	}


	//rotated quads
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color) {
		s_Data->CombinedShader->SetFloat4(color, "u_Color");  //upload color
		s_Data->CombinedShader->SetFloat(1.0f, "u_TexScale");

		s_Data->WhiteTexture->Bind(0); //bind a solid white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		s_Data->CombinedShader->SetMat4(transform, "u_Transform");

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data->QuadVertexArray);
	}

	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, texture, texScale);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		s_Data->CombinedShader->SetFloat4(tint, "u_Color");  
		s_Data->CombinedShader->SetFloat(texScale, "u_TexScale");

		texture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->CombinedShader->SetMat4(transform, "u_Transform");

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data->QuadVertexArray);
	}


}
