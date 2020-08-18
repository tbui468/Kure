#include "krpch.h"
#include "FrameBuffer.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Kure {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLFrameBuffer>(spec);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}
}
