#include "krpch.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Kure {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec) : m_Specification(spec){
		Invalidate();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
		glDeleteFramebuffers(1, &m_RendererID);

	}

	void OpenGLFrameBuffer::Invalidate() {
	
		//THIS MIGHT BE THE PROBLEM WITH FLICKERIN AND BLACK SCREEN
		if (m_RendererID) {
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
			glDeleteFramebuffers(1, &m_RendererID);
		}

		glCreateFramebuffers(1, &m_RendererID);
		Bind();

		//COLOR ATTACHMENT
		//create color attachment (color buffer)
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		//set color attachment properties
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//set color attachment to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);


		//DEPTH ATTACHMENT
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		KR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		Unbind();
	}


	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
		if (width == 0 || height == 0 || width > 8192 || height > 8192) {
			KR_CORE_WARN("Attempted to resize frame buffer to {0}, {1}", width, height);
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		Invalidate();
	}


	void OpenGLFrameBuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFrameBuffer::Unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
