#include "krpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Kure {


	glm::mat4 Renderer::m_ViewProjectionMatrix = glm::mat4(1.0f);

	void Renderer::Init() {
		RenderCommand::Init();
	}


	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera) {
		m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::Submit(const VertexArray& vertexArray, const glm::mat4& transform, Shader& shader) {
		shader.Bind();
		dynamic_cast<OpenGLShader*>(&shader)->UploadUniformMat4(m_ViewProjectionMatrix, "u_ViewProjMatrix"); 
		dynamic_cast<OpenGLShader*>(&shader)->UploadUniformMat4(transform, "u_Transform"); 
		vertexArray.Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::EndScene() {

	}

}