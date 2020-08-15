#pragma once

#include <Kure.h>
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp> 

class Sandbox2D : public Kure::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Kure::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Kure:: Event& event) override;
private:
	Kure::Ref<Kure::OrthographicCameraController> m_CameraController;
	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	Kure::Ref<Kure::Texture2D> m_Texture;
	Kure::Ref<Kure::Texture2D> m_SpriteSheet;
	Kure::Ref<Kure::Texture2D> m_SquaresTexture;
};

