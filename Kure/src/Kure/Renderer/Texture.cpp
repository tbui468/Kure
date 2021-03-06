#include "krpch.h"
#include "Texture.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Kure {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None: {
			KR_CORE_ASSERT(false, "RendererAPI::None is currently selcted");
			return nullptr;
		}
		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLTexture2D>(width, height);
		}
		}
		KR_CORE_ASSERT(false, "No valid renderer API specified!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None: {
			KR_CORE_ASSERT(false, "RendererAPI::None is currently selcted");
			return nullptr;
		}
		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLTexture2D>(path);
		}
		}
		KR_CORE_ASSERT(false, "No valid renderer API specified!");
		return nullptr;
	}



}


