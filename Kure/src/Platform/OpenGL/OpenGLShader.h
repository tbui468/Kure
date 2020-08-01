#pragma once

#include "Kure/Renderer/Shader.h"

namespace Kure {

	class OpenGLShader : public Shader
	{
	public:
		virtual ~OpenGLShader() = default;
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual void Bind() const override;
		virtual void Unbind() const override;

	public: //uniform uploads
		void UploadUniformInt(int value, const std::string& name) const;

		void UploadUniformFloat(float value, const std::string& name) const;
		void UploadUniformFloat2(glm::vec2 vec, const std::string& name) const;
		void UploadUniformFloat3(glm::vec3 vec, const std::string& name) const;
		void UploadUniformFloat4(glm::vec4 vec, const std::string& name) const;

		void UploadUniformMat3(glm::mat3 matrix, const std::string& name) const;
		void UploadUniformMat4(glm::mat4 matrix, const std::string& name) const;
	private:
		uint32_t m_RendererID;
	};

}

