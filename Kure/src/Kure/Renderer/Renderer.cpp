#include "krpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Kure {

	void Renderer::BeginScene() {
		//give all environment properties
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		//submit to render command queue 
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::EndScene() {

	}

}