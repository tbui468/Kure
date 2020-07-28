#pragma once

#include <string>

namespace Kure {

	//interface for different rendering API shaders
	class Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};


}

