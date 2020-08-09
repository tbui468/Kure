#include "krpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Kure/Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Kure {


	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) {
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &height, &width, &channels, 0);

		KR_CORE_ASSERT(data, "Failed to load image");

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0;
		GLenum dataFormat = 0;

		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		KR_CORE_ASSERT(internalFormat & dataFormat, "Invalid color channels in texture!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID); //create texture
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height); //size

		//set interpolation settings
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererID);
	}



}
