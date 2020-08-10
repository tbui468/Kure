#include "Sandbox2D.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(std::make_shared<Kure::OrthographicCameraController>(1280.0f / 720.0f, true)){
}


void Sandbox2D::OnAttach() {
	Kure::Renderer2D::Init();
}
void Sandbox2D::OnDetach() {
	Kure::Renderer2D::Shutdown();
}
void Sandbox2D::OnUpdate(Kure::TimeStep ts) {
	m_CameraController->OnUpdate(ts);

	//Render commands here
	Kure::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.5f, 1.0f });
	Kure::RenderCommand::Clear();

	Kure::Renderer2D::BeginScene(m_CameraController->GetCamera());
	Kure::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Color);
	Kure::Renderer2D::EndScene();

//	dynamic_cast<Kure::OpenGLShader*>(m_FlatShader.get())->UploadUniformFloat4(m_Color, "u_Color");  //upload color
//	m_Texture->Bind(0);  //texture slots and uniforms are not workint correctly
//	Kure::Renderer::Submit(*m_VertexArray, glm::mat4(1.0f), *m_TextureShader);

}
void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Color Picker");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));
	ImGui::End();
}
void Sandbox2D::OnEvent(Kure::Event& event) {
	m_CameraController->OnEvent(event);
}
