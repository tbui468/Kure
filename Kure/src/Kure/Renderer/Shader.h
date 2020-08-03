#pragma once

#include "glm/glm.hpp"
#include "Kure/Core.h"

namespace Kure {

	//interface for different rendering API shaders
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};


}

