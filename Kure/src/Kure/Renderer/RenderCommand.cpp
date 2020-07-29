#include "krpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kure {
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
