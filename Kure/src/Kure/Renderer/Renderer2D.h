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

		static void DrawQuad(const glm::vec2& position, float angle, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, float angle, const glm::vec2& size, const glm::vec4& color); //extra position dimension for depth
		static void DrawQuad(const glm::vec2& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, float angle, const glm::vec2& size, const Ref<Texture2D>& texture); //extra position dimension for depth
	private:
	};

}

