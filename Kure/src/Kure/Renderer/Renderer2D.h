#pragma once

#include "Kure/Renderer/OrthographicCamera.h"
#include "Kure/Renderer/Texture.h"
#include "Kure/Renderer/SubTexture2D.h"

namespace Kure {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

		static void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);

		//draw non-rotated quads
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, 
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, 
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));

		//draw quads with transformation matrix
		static void DrawQuad(const glm::mat4& transformation, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transformation, const Ref<Texture2D>& texture, float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transformation, const Ref<SubTexture2D>& subTexture, float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));

		//draw rotated quads
		static void DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color); 
		static void DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<SubTexture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<SubTexture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));


		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
		};

		static Statistics GetStats();

		static void ResetStats();

	private:
		static void StartAnotherBatch();
		static void InitBatch();
	};

}

