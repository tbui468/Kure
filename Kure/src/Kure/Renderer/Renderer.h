#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "Camera.h"

namespace Kure {


	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(const Camera& camera); 
		static void Submit(const VertexArray& vertexArray, const glm::mat4& transform, Shader& shader);
		static void EndScene();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static glm::mat4 m_ViewProjectionMatrix;
	};

}
