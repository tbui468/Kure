#pragma once

#include "Kure/Renderer/RendererAPI.h"

namespace Kure {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const VertexArray& vertexArray) override;
	};



}
