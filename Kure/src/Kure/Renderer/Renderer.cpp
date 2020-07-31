#include "krpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Kure {


	glm::mat4 Renderer::m_ViewProjectionMatrix = glm::mat4(1.0f);

	void Renderer::BeginScene(const Camera& camera) {
		m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::Submit(const VertexArray& vertexArray, const Shader& shader, const glm::mat4& transform) {
		shader.Bind();
		shader.UploadUniformMat4(m_ViewProjectionMatrix, "u_ViewProjMatrix");
		shader.UploadUniformMat4(transform, "u_Transform");
		vertexArray.Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::EndScene() {

	}

}