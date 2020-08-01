#pragma once

#include "Kure/Renderer/RendererAPI.h"

namespace Kure {


	class RenderCommand
	{
	public:
		inline static void DrawIndexed(const VertexArray& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}
		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}
	private:
		static RendererAPI* s_RendererAPI; //point to specific rendererAPI (eg, OpenGL, DirectX, etc)
	};

}
