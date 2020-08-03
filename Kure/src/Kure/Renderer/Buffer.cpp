#include "krpch.h"
#include "Buffer.h"

#include "Kure/Log.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Kure {

//create functions for vertex and index buffer here based on rendererAPI

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}


}
