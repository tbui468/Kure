#pragma once

#include "Kure/Renderer/Texture.h"
#include <glm/glm.hpp>

namespace Kure {

	class SubTexture2D
	{
	public: 
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTextureCoordinates() const { return m_TexCoords; }

		//helper function to create subtexture
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, float x, float y, 
									const glm::vec2& spriteUnitSize, const glm::vec2& spriteRatio = glm::vec2{ 1.0f, 1.0f });
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};


}

