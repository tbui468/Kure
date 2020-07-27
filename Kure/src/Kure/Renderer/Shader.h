#pragma once

#include <string>

namespace Kure {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		void Bind();
		void Unbind(); //only for debug purposes
	private:
		uint32_t m_RendererID;
	};


}

