#pragma once


namespace Kure {

	struct FrameBufferSpecification {
		uint32_t Width = 0;
		uint32_t Height = 0;
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
		virtual ~FrameBuffer() = default;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
		virtual void Invalidate() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
	private:
	};

}

