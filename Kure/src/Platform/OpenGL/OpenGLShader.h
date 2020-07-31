#pragma once

#include "Kure/Renderer/Shader.h"

namespace Kure {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void UploadUniformMat4(glm::mat4 matrix, const std::string& name) const override;
	private:
		uint32_t m_RendererID;
	};

}

