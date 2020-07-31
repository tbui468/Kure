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
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer);
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		//can these be unique pointers?  Or just allocated on the stack???
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};


}

