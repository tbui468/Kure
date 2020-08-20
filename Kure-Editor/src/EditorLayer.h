#pragma once

#include <Kure.h>

#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp> 

namespace Kure {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		Ref<OrthographicCameraController> m_CameraController;
		glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<Texture2D> m_SquaresTexture;
		Ref<SubTexture2D> m_BarrelSubTexture;
		Ref<SubTexture2D> m_GrassSubTexture;
		Ref<SubTexture2D> m_DirtSubTexture;
		Ref<SubTexture2D> m_WaterSubTexture;
		std::unordered_map<char, Ref<SubTexture2D>> m_TextureMap;
		Ref<FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};


}
