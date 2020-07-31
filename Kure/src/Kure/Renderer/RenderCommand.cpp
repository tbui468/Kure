#include "krpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kure {

	RendererAPI* RenderCommand::s_RendererAPI = []()->RendererAPI* {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::OpenGL: return new OpenGLRendererAPI;
			//case RendererAPI::API::DirectX: return new DirectXRendererAPI;
			//case RendererAPI::API::Vulkan: return new VulkanRendererAPI;
			//case RendererAPI::API::Metal: return new MetalRendererAPI;
		}
		KR_CORE_ASSERT(false, "No renderer specified!");
		return nullptr;
	}(); //need the () at the end because I want to assign s_RendererAPI to the result of the lambda, not the lambda itself

}
