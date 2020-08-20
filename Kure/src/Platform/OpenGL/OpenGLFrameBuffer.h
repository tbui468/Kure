#pragma once

#include "Kure/Renderer/FrameBuffer.h"

namespace Kure {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		virtual void Invalidate() override; //meaning: state is invalid, so recreate frame buffer
		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; } //to give to ImGui
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FrameBufferSpecification  m_Specification;
	};

}

