#include "krpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Kure/Renderer/RenderCommand.h"


#include <glm/gtc/type_ptr.hpp> 

namespace Kure {


	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData {
		const uint32_t MaxQuadsPerDrawCall = 10000;
		const uint32_t MaxVerticesPerDrawCall = MaxQuadsPerDrawCall * 4;
		const uint32_t MaxIndicesPerDrawCall = MaxQuadsPerDrawCall * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> CombinedShader; //combined flat color shader and texture shader
		Ref<Texture> WhiteTexture;

		uint32_t QuadIndexCount = 0; //increment by 6 (indices per quad) everytime we draw a quad
		QuadVertex* QuadVertexBufferBase = nullptr; //what is this for?
		QuadVertex* QuadVertexBufferPtr = nullptr; //what is this for?
	};

	static Renderer2DData s_Data;


	void Renderer2D::Init() {
		KR_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVerticesPerDrawCall * sizeof(QuadVertex));
		BufferLayout layout = {
			{ShaderDataType::Float3, "vertex"},
			{ShaderDataType::Float4, "color"},
			{ShaderDataType::Float2, "texCoord"}
		};
		s_Data.QuadVertexBuffer->SetLayout(layout);

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVerticesPerDrawCall]; //initialize this shit

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndicesPerDrawCall];

		uint32_t offset = 0;
		for (uint32_t index = 0; index < s_Data.MaxIndicesPerDrawCall; index += 6) {
			quadIndices[index] = offset;
			quadIndices[index + 1] = offset + 1;
			quadIndices[index + 2] = offset + 2;
			quadIndices[index + 3] = offset + 2;
			quadIndices[index + 4] = offset + 3;
			quadIndices[index + 5] = offset;
			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndicesPerDrawCall);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] quadIndices;

		//create white texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t data = 0xffffffff;
		s_Data.WhiteTexture->SetData(&data, sizeof(uint32_t));

		//combined flat color and texture shader
		s_Data.CombinedShader = Shader::Create("assets/shaders/Combined.glsl");
		s_Data.CombinedShader->Bind();
		s_Data.CombinedShader->SetInt(0, "u_Texture");
	}
	void Renderer2D::Shutdown() {
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		//batch everything here
		s_Data.CombinedShader->Bind();
		s_Data.CombinedShader->SetMat4(camera.GetViewProjectionMatrix(), "u_ViewProjMatrix");
		
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}
	void Renderer2D::EndScene() {
		//move verterx buffer data to GPU side
		uint32_t size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);
		Flush();
	}

	void Renderer2D::Flush() {
		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}


	//axis aligned quads
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		/*
		s_Data.CombinedShader->SetFloat4(color, "u_Color");  //upload color
		s_Data.CombinedShader->SetFloat(1.0f, "u_TexScale");

		s_Data.WhiteTexture->Bind(0); //bind a solid white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		s_Data.CombinedShader->SetMat4(transform, "u_Transform");

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray);*/
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, texScale, tint);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		s_Data.CombinedShader->SetFloat4(tint, "u_Color");  
		s_Data.CombinedShader->SetFloat(texScale, "u_TexScale");

		texture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.CombinedShader->SetMat4(transform, "u_Transform");

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray);
	}


	//rotated quads
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color) {
		s_Data.CombinedShader->SetFloat4(color, "u_Color");  //upload color
		s_Data.CombinedShader->SetFloat(1.0f, "u_TexScale");

		s_Data.WhiteTexture->Bind(0); //bind a solid white texture

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		s_Data.CombinedShader->SetMat4(transform, "u_Transform");

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray);
	}

	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, texture, texScale);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		s_Data.CombinedShader->SetFloat4(tint, "u_Color");  
		s_Data.CombinedShader->SetFloat(texScale, "u_TexScale");

		texture->Bind(0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.CombinedShader->SetMat4(transform, "u_Transform");

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray);
	}


}
