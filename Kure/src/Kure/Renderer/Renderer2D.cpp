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
		float TexIndex;
		float TexScale;
	};

	struct Renderer2DData {
		static const uint32_t MaxQuadsPerDrawCall = 20000;
		static const uint32_t MaxVerticesPerDrawCall = MaxQuadsPerDrawCall * 4;
		static const uint32_t MaxIndicesPerDrawCall = MaxQuadsPerDrawCall * 6;
		static const uint32_t MaxTextureSlots = 32; //TODO: RenderCapabilities
		static const glm::vec4 QuadVertexPos[];
		static const glm::vec2 TexCoordPos[];

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> CombinedShader; //combined flat color shader and texture shader
		Ref<Texture> WhiteTexture;

		uint32_t QuadIndexCount = 0; //increment by 6 (indices per quad) everytime we draw a quad
		QuadVertex* QuadVertexBufferBase = nullptr; 
		QuadVertex* QuadVertexBufferPtr = nullptr; 

		std::array<Ref<Texture>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; //0 = white texture


		Renderer2D::Statistics Stats;
	};


	const glm::vec4 Renderer2DData::QuadVertexPos[] =
	{ { -0.5, -0.5, 0.0, 1.0f },
	{ 0.5, -0.5, 0.0, 1.0f },
	{ 0.5, 0.5, 0.0, 1.0f },
	{ -0.5, 0.5, 0.0, 1.0f } };


	const glm::vec2 Renderer2DData::TexCoordPos[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
	


	static Renderer2DData s_Data;


	void Renderer2D::Init() {
		KR_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxVerticesPerDrawCall * sizeof(QuadVertex));
		BufferLayout layout = {
			{ShaderDataType::Float3, "vertex"},
			{ShaderDataType::Float4, "color"},
			{ShaderDataType::Float2, "texCoord"},
			{ShaderDataType::Float, "texIndex"},
			{ShaderDataType::Float, "texScale"}

		};
		s_Data.QuadVertexBuffer->SetLayout(layout);

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVerticesPerDrawCall]; //initialize this shit

		uint32_t* quadIndices = new uint32_t[Renderer2DData::MaxIndicesPerDrawCall];

		uint32_t offset = 0;
		for (uint32_t index = 0; index < Renderer2DData::MaxIndicesPerDrawCall; index += 6) {
			quadIndices[index] = offset;
			quadIndices[index + 1] = offset + 1;
			quadIndices[index + 2] = offset + 2;
			quadIndices[index + 3] = offset + 2;
			quadIndices[index + 4] = offset + 3;
			quadIndices[index + 5] = offset;
			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, Renderer2DData::MaxIndicesPerDrawCall);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] quadIndices;


		//combined shader (color and texture shader)
		s_Data.CombinedShader = Shader::Create("assets/shaders/Combined.glsl");

		int32_t samplers[Renderer2DData::MaxTextureSlots];
		//this is just 0 - 31????
		//setting uniform (array of ints) to 0 to 31
		for (uint32_t i = 0; i < Renderer2DData::MaxTextureSlots; ++i) {
			samplers[i] = i;
		}
		s_Data.CombinedShader->Bind();
		s_Data.CombinedShader->SetIntArray(samplers, Renderer2DData::MaxTextureSlots, "u_Textures");

		//create and assign white texture to texture slot 0
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t data = 0xffffffff;
		s_Data.WhiteTexture->SetData(&data, sizeof(uint32_t));
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

	}

	void Renderer2D::Shutdown() {
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		//batch everything here
		s_Data.CombinedShader->Bind();
		s_Data.CombinedShader->SetMat4(camera.GetViewProjectionMatrix(), "u_ViewProjMatrix");

		InitBatch();
	}

	void Renderer2D::EndScene() {
		uint32_t size = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);
		Flush();
	}

	void Renderer2D::Flush() {

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; ++i) {
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(*s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}


	void Renderer2D::StartAnotherBatch() {
		EndScene();
		InitBatch();
	}


	void Renderer2D::InitBatch() {
		s_Data.QuadIndexCount = 0;
		s_Data.TextureSlotIndex = 1;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}


	void Renderer2D::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color) {

	}


	//axis aligned quads
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		float textureIndex = 0.0f; //white
		float texScale = 1.0f;

		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; ++i) {
				s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
				s_Data.QuadVertexBufferPtr->TexCoord = Renderer2DData::TexCoordPos[i];
				s_Data.QuadVertexBufferPtr->Color = color;
				s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
				s_Data.QuadVertexBufferPtr->TexScale = texScale;
				s_Data.QuadVertexBufferPtr++;
		}


		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;

	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, texScale, tint);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {



		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		glm::vec4 color(1.0f);

		//check if texture is already loaded
		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if texture is not alreading in TextureSlots, add it inside
		//increment TExtureSLotIndex
		if (textureIndex == 0) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}


		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		for (int i = 0; i < 4; ++i) {
				s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
				s_Data.QuadVertexBufferPtr->TexCoord = Renderer2DData::TexCoordPos[i];
				s_Data.QuadVertexBufferPtr->Color = color;
				s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
				s_Data.QuadVertexBufferPtr->TexScale = texScale;
				s_Data.QuadVertexBufferPtr++;
		}


		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;

	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float texScale, const glm::vec4& tint) {
		DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, texScale, tint);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float texScale, const glm::vec4& tint) {



		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		glm::vec4 color(1.0f);

		//check if texture is already loaded
		float textureIndex = 0.0f;
		const Ref<Texture2D> texture = subTexture->GetTexture();


		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}


		//if texture is not alreading in TextureSlots, add it inside
		//increment TExtureSLotIndex
		if (textureIndex == 0) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}


		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });



		const glm::vec2* texCoords = subTexture->GetTextureCoordinates();

		for (int i = 0; i < 4; ++i) {
			s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TexScale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}



		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;


	}


	//rotated quads
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color) {


		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		float textureIndex = 0.0f; //white
		float texScale = 1.0f;

		for (int i = 0; i < 4; ++i) {
			s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = Renderer2DData::TexCoordPos[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TexScale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}


		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, texture, texScale);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {


		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		glm::vec4 color(1.0f);

		//check if texture is already loaded
		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if texture is not alreading in TextureSlots, add it inside
		//increment TExtureSLotIndex
		if (textureIndex == 0) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}


		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; ++i) {
			s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = Renderer2DData::TexCoordPos[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TexScale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}



		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float texScale, const glm::vec4& tint) {
		DrawRotatedQuad({ position.x, position.y, 0.0f }, angle, size, subTexture, texScale);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float texScale, const glm::vec4& tint) {


		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall) {
			StartAnotherBatch();
		}

		glm::vec4 color(1.0f);

		//check if texture is already loaded
		float textureIndex = 0.0f;

		const Ref<Texture2D> texture = subTexture->GetTexture();

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		//if texture is not alreading in TextureSlots, add it inside
		//increment TExtureSLotIndex
		if (textureIndex == 0) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}


		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		const glm::vec2* texCoords = subTexture->GetTextureCoordinates();

		for (int i = 0; i < 4; ++i) {
			s_Data.QuadVertexBufferPtr->Position = transformation * Renderer2DData::QuadVertexPos[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TexScale = texScale;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}



	Renderer2D::Statistics Renderer2D::GetStats() {
		return s_Data.Stats;
	}

	void Renderer2D::ResetStats() {
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

}
