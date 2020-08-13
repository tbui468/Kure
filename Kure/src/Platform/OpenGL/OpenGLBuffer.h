#pragma once

#include "Kure/Renderer/Buffer.h"

namespace Kure {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetData(const void* data, uint32_t size) const override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		BufferLayout m_Layout;
		unsigned int m_RendererID;
	};


	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		unsigned int m_RendererID;
	};

}

