#pragma once

#include "RendererAPI.h"

namespace Kure {


	class Renderer {
	public:
		static void BeginScene(); //why static functions?
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
