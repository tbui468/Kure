#pragma once

#include <memory>
#include "Kure/Renderer/Buffer.h"
#include "Kure/Core/Core.h"

namespace Kure {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		static Ref<VertexArray> Create();
	};


}

