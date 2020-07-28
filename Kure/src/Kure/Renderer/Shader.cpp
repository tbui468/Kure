#include "krpch.h"
#include "Kure/Log.h"
#include "Shader.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Kure {

	
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}


}
