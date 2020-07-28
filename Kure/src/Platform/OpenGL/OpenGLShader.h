#pragma once

#include "Kure/Renderer/Shader.h"

namespace Kure {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_RendererID;
	};

}

