#include "krpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>


namespace Kure {


	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int:   return GL_INT;
		case ShaderDataType::Int2:  return GL_INT;
		case ShaderDataType::Int3:  return GL_INT;
		case ShaderDataType::Int4:  return GL_INT;
		case ShaderDataType::MatF3: return GL_FLOAT;
		case ShaderDataType::MatF4: return GL_FLOAT;
		case ShaderDataType::Bool:  return GL_BOOL;
		}

		KR_CORE_ASSERT(false, "Invalid ShaderDataType");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}


	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		Bind();

		//make sure vertexbuffer has layout
		KR_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(), "Vertex buffer layout not specified");

		vertexBuffer->Bind();
		BufferLayout layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const BufferElement& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);

	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		Bind();
		m_IndexBuffer = indexBuffer;
	}


}
