#include "Sandbox2D.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(std::make_shared<Kure::OrthographicCameraController>(1280.0f / 720.0f, true)){
	KR_PROFILE_FUNCTION();
}


void Sandbox2D::OnAttach() {
	KR_PROFILE_FUNCTION();
	m_Texture = Kure::Texture2D::Create("assets/textures/texture.png");
}
void Sandbox2D::OnDetach() {
	KR_PROFILE_FUNCTION();
}
void Sandbox2D::OnUpdate(Kure::TimeStep ts) {
	KR_PROFILE_FUNCTION();

	{
		KR_PROFILE_SCOPE("Camera Controller Onupdate()");
		m_CameraController->OnUpdate(ts);
	}

	{
		KR_PROFILE_SCOPE("Clear Buffer");
		Kure::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Kure::RenderCommand::Clear();
	}

	{
		KR_PROFILE_SCOPE("Begin scene setup");
		Kure::Renderer2D::BeginScene(m_CameraController->GetCamera());
	}
	{
		KR_PROFILE_SCOPE("Render 3 quads");
//		Kure::Renderer2D::DrawRotatedQuad({ 0.0f, 0.5f }, 0.1f, { 1.0f, 1.0f }, m_Color);
		Kure::Renderer2D::DrawQuad({ -0.7f, -0.1f }, { 2.0f, 0.8f }, { 0.5f, 0.2f, 0.8f, 1.0f });
		Kure::Renderer2D::DrawQuad({ 0.7f, 0.1f }, { 1.0f, 1.0f }, { 0.5f, 0.8f, 0.3f, 1.0f });
//		Kure::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f, -.1f }, 0.1f, { 2.0f, 2.0f }, m_Texture, 2.0f, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));
//		Kure::Renderer2D::DrawQuad({ -0.5f, 0.5f, -.1f }, { 2.0f, 2.0f }, m_Texture, 2.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));
	}
	{
		KR_PROFILE_SCOPE("End scene");
		Kure::Renderer2D::EndScene();
	}

	//	dynamic_cast<Kure::OpenGLShader*>(m_FlatShader.get())->UploadUniformFloat4(m_Color, "u_Color");  //upload color
	//	m_Texture->Bind(0);  //texture slots and uniforms are not workint correctly
	//	Kure::Renderer::Submit(*m_VertexArray, glm::mat4(1.0f), *m_TextureShader);

}
void Sandbox2D::OnImGuiRender() {
	KR_PROFILE_FUNCTION();
	ImGui::Begin("Color Picker");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));
	ImGui::End();
}
void Sandbox2D::OnEvent(Kure::Event& event) {
	KR_PROFILE_FUNCTION();
	m_CameraController->OnEvent(event);
}
