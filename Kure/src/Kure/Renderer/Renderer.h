#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "Camera.h"

namespace Kure {


	class Renderer {
	public:
		static void BeginScene(const Camera& camera); 
		static void Submit(const VertexArray& vertexArray, Shader& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static glm::mat4 m_ViewProjectionMatrix;
	};

}
