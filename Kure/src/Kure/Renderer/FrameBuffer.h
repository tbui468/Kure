#pragma once


namespace Kure {

	struct FrameBufferSpecification {
		uint32_t Width;
		uint32_t Height;
		//format
		uint32_t Samples = 1;
		////SwapChainTarget
		//when true, render directly to screen (so not really using frame buffer)
		//when false, render to the frame buffer
		bool SwapChainTarget = false; 
	};

	class FrameBuffer
	{
	public:
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
		virtual void Invalidate() = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
	private:
	};

}

