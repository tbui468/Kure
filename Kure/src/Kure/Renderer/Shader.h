#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Kure {

	//interface for different rendering API shaders
	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void UploadUniformMat4(glm::mat4 matrix, const std::string& name) const = 0;
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};


}

