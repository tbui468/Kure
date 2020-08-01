#pragma once

#include "Kure/Renderer/VertexArray.h"


namespace Kure {


	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		virtual void Bind() const;
		virtual void Unbind() const;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer);
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		//can these be unique pointers?  Or just allocated on the stack???
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};


}

