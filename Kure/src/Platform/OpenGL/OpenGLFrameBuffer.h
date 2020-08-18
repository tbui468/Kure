#pragma once

#include "Kure/Renderer/FrameBuffer.h"

namespace Kure {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		virtual void Invalidate() override; //meaning: state is invalid, so recreate frame buffer
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; } //to give to ImGui
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FrameBufferSpecification  m_Specification;
	};

}

