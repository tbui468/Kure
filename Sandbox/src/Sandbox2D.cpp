#include "Sandbox2D.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(std::make_shared<Kure::OrthographicCameraController>(1280.0f / 720.0f, false)){
	KR_PROFILE_FUNCTION();
}


void Sandbox2D::OnAttach() {
	KR_PROFILE_FUNCTION();
	m_Texture = Kure::Texture2D::Create("assets/textures/texture.png");
	m_SpriteSheet = Kure::Texture2D::Create("assets/game/RPGpack_sheet_2X.png");
	m_SquaresTexture = Kure::Texture2D::Create("assets/textures/squaresTexture.png");
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
		Kure::Renderer2D::ResetStats();
	}


#if 0
	{
		KR_PROFILE_SCOPE("Begin scene setup");
		Kure::Renderer2D::BeginScene(m_CameraController->GetCamera());
	}
	{
		KR_PROFILE_SCOPE("Render 3 quads"); //negative z is further away from camera (0 is at camera)
		Kure::Renderer2D::DrawRotatedQuad({ 0.0f, -0.5f , -0.8f}, glm::radians(45.0f), { 1.0f, 1.0f }, m_Color);
		Kure::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f , -0.5f}, glm::radians(60.0f), { 1.0f, 1.0f }, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		Kure::Renderer2D::DrawQuad({ -0.7f, -0.1f }, { 2.0f, 0.8f }, { 0.5f, 0.2f, 0.8f, 1.0f });
		Kure::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f, -0.1f }, glm::radians(180.0f), { 1.0f, 1.0f }, m_Texture, 2.0f, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));
		Kure::Renderer2D::DrawQuad({ 0.0f, 0.0f, -.9f }, { 10.0f, 10.0f }, m_Texture, 1.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));
		/*
		Kure::Renderer2D::DrawQuad({ 0.7f, 0.1f }, { 1.0f, 1.0f }, { 0.5f, 0.8f, 0.3f, 1.0f });
		Kure::Renderer2D::DrawQuad({ -0.5f, 0.5f, -.1f }, { 1.0f, 1.0f }, m_Texture, 12.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));
		Kure::Renderer2D::DrawQuad({ -0.5f, -1.0f, -.1f }, { 1.0f, 1.0f }, m_SquaresTexture, 2.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));*/


		for (int i = -50; i < 50; ++i) {
			for (int j = -50; j < 50; ++j) {
				Kure::Renderer2D::DrawQuad({ (float)i, (float)j }, { 0.9f, 0.9f }, { ((float)i + 50.0f) / 100.0f, 0.2f, ((float)j + 50.0f) / 100.0f, 0.5f });
			}
		}
	}
	{
		KR_PROFILE_SCOPE("End scene");
		Kure::Renderer2D::EndScene();
	}
#endif

		Kure::Renderer2D::BeginScene(m_CameraController->GetCamera());
		Kure::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_SpriteSheet, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Kure::Renderer2D::EndScene();



	//	dynamic_cast<Kure::OpenGLShader*>(m_FlatShader.get())->UploadUniformFloat4(m_Color, "u_Color");  //upload color
	//	m_Texture->Bind(0);  //texture slots and uniforms are not workint correctly
	//	Kure::Renderer::Submit(*m_VertexArray, glm::mat4(1.0f), *m_TextureShader);

}
void Sandbox2D::OnImGuiRender() {
	KR_PROFILE_FUNCTION();
	ImGui::Begin("Color Picker");

	Kure::Renderer2D::Statistics stats = Kure::Renderer2D::GetStats();
	ImGui::Text("Rendering Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);

	ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));
	ImGui::End();
}
void Sandbox2D::OnEvent(Kure::Event& event) {
	KR_PROFILE_FUNCTION();
	m_CameraController->OnEvent(event);
}
