#pragma once

#include "Kure/Renderer/Shader.h"

//TODO: REMOVE!
typedef unsigned int GLenum;

namespace Kure {

	class OpenGLShader : public Shader
	{
	public:
		virtual ~OpenGLShader() = default;
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(int value, const std::string& name) override;
		virtual void SetFloat3(const glm::vec3& value, const std::string& name) override;
		virtual void SetFloat4(const glm::vec4& value, const std::string& name) override;
		virtual void SetMat4(const glm::mat4& value, const std::string& name) override;

		virtual const std::string& GetName() const override { return m_Name; }

	public: //uniform uploads
		void UploadUniformInt(int value, const std::string& name) const;

		void UploadUniformFloat(float value, const std::string& name) const;
		void UploadUniformFloat2(glm::vec2 vec, const std::string& name) const;
		void UploadUniformFloat3(glm::vec3 vec, const std::string& name) const;
		void UploadUniformFloat4(glm::vec4 vec, const std::string& name) const;

		void UploadUniformMat3(glm::mat3 matrix, const std::string& name) const;
		void UploadUniformMat4(glm::mat4 matrix, const std::string& name) const;
	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string ReadFile(const std::string& filepath);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}

