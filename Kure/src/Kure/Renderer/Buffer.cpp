#include "krpch.h"
#include "Buffer.h"

#include "Kure/Log.h"
#include "Kure/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Kure {

//create functions for vertex and index buffer here based on rendererAPI

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(unsigned int* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:   KR_CORE_ASSERT(false, "Renderer API not specified"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, count);
		}

		KR_CORE_ASSERT(false, "Specified Renderer API not defined!");
		return nullptr;
	}


}
