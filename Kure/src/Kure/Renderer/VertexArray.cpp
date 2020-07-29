#include "krpch.h"
#include "VertexArray.h"

#include "Kure/Log.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Kure {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}

}
