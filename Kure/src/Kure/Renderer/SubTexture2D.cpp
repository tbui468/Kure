#include "krpch.h"
#include "SubTexture2D.h"

namespace Kure {


	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) 
	: m_Texture(texture) {
		KR_CORE_ASSERT(m_Texture, "m_Texture is null ptr");
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}


	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, float x, float y, const glm::vec2& spriteUnitSize, const glm::vec2& spriteRatio) {
		float sheetWidth = texture->GetWidth();
		float sheetHeight = texture->GetHeight();
		glm::vec2 min = { x * spriteUnitSize.x / sheetWidth, y * spriteUnitSize.y / sheetHeight };
		glm::vec2 max = { (x + spriteRatio.x) * spriteUnitSize.x / sheetWidth, (y + spriteRatio.y) * spriteUnitSize.y / sheetHeight };
		return CreateRef<SubTexture2D>(texture, min, max);
	}


}
