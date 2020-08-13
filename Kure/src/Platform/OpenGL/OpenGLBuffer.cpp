#include "krpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Kure {

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
		KR_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		KR_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		KR_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		KR_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		KR_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size) const {
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}



	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, uint32_t count) : m_Count(count) {
		KR_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		KR_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const {
		KR_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::Unbind() const {
		KR_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
