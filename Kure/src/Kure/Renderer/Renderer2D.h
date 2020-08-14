#pragma once

#include "Kure/Renderer/OrthographicCamera.h"
#include "Kure/Renderer/Texture.h"

namespace Kure {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

		//draw non-rotated quads
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, 
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));

		//draw rotated quads
		static void DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color); 
		static void DrawRotatedQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture,
								float texScale = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture,
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

