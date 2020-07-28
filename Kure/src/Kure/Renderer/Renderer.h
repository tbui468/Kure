#pragma once

namespace Kure {


	enum class RendererAPI {
		None = 0,
		OpenGL
	};

	class Renderer {
	public:
		inline static void SetAPI(RendererAPI api) { s_RendererAPI = api; }
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};

}
