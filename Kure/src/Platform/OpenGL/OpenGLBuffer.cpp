#include "krpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Kure {


	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		glCreateBuffers(1, &m_RendererID);
		Bind();

		//load to gpu
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, uint32_t count) : m_Count(count) {
		glCreateBuffers(1, &m_RendererID);
		Bind();

		//load to gpu
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
