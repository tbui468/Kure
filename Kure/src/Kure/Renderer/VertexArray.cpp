#include "krpch.h"
#include "Kure/Renderer/VertexArray.h"

#include "Kure/Core/Log.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Kure {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexArray>();
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}

}
