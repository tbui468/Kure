#include "Sandbox2D.h"

static const uint32_t mapWidth = 24;
static const uint32_t mapHeight = 24;
static const char* s_MapTiles = "WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWDWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWGWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWKWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(std::make_shared<Kure::OrthographicCameraController>(1280.0f / 720.0f, false)){
	KR_PROFILE_FUNCTION();
}


void Sandbox2D::OnAttach() {
	KR_PROFILE_FUNCTION();
	m_Texture = Kure::Texture2D::Create("assets/textures/texture.png");
	m_SpriteSheet = Kure::Texture2D::Create("assets/game/RPGpack_sheet_2X.png");
	m_SquaresTexture = Kure::Texture2D::Create("assets/textures/squaresTexture.png");

	//m_TreeSubTexture = Kure::SubTexture2D::CreateFromCoords(m_SpriteSheet, 2, 1, { 128.0f, 128.0f }, { 1.0f, 2.0f });
	m_BarrelSubTexture = Kure::SubTexture2D::CreateFromCoords(m_SpriteSheet, 9, 0, { 128.0f, 128.0f });
	m_GrassSubTexture = Kure::SubTexture2D::CreateFromCoords(m_SpriteSheet, 1, 11, { 128.0f, 128.0f });
	m_DirtSubTexture = Kure::SubTexture2D::CreateFromCoords(m_SpriteSheet, 6, 11, { 128.0f, 128.0f });
	m_WaterSubTexture = Kure::SubTexture2D::CreateFromCoords(m_SpriteSheet, 11, 11, { 128.0f, 128.0f });

	m_TextureMap['W'] = m_WaterSubTexture;
	m_TextureMap['D'] = m_DirtSubTexture;
	m_TextureMap['G'] = m_GrassSubTexture;

	m_CameraController->SetZoom(5.0f);

	Kure::FrameBufferSpecification frameBufferSpec;
	frameBufferSpec.Width = 1280;
	frameBufferSpec.Height = 720;
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
//		Kure::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_SpriteSheet, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//		Kure::Renderer2D::DrawQuad({ 1.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_GrassSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//		Kure::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_DirtSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		for (int32_t row = 0; row < mapWidth; ++row) {
			for (int32_t col = 0; col < mapHeight; ++col) {
				//get correct char c from s_MapTiles
				//get subtexture t from m_TextureMap using c
				//draw quad with subtexture t with 
				char c = s_MapTiles[col + (mapHeight - 1 - row) * mapWidth];
				Kure::Ref<Kure::SubTexture2D> texture;
				if (m_TextureMap.find(c) != m_TextureMap.end()) {
					texture = m_TextureMap[c];
				}
				else {
					texture = m_BarrelSubTexture;
				}

				Kure::Renderer2D::DrawQuad({ col - 12, row - 12, -0.1f }, { 1.0f, 1.0f }, texture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}



//		Kure::Renderer2D::DrawRotatedQuad({ 1.0f, 1.0f, -0.1f }, glm::radians(45.0f), { 1.0f, 2.0f }, m_TreeSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//		Kure::Renderer2D::DrawRotatedQuad({ 0.0f, 1.5f, -0.1f }, glm::radians(180.0f), { 1.0f, 1.0f }, m_BarrelSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Kure::Renderer2D::EndScene();



	//	dynamic_cast<Kure::OpenGLShader*>(m_FlatShader.get())->UploadUniformFloat4(m_Color, "u_Color");  //upload color
	//	m_Texture->Bind(0);  //texture slots and uniforms are not workint correctly
	//	Kure::Renderer::Submit(*m_VertexArray, glm::mat4(1.0f), *m_TextureShader);

}
void Sandbox2D::OnImGuiRender() {

	KR_PROFILE_FUNCTION();




	//all nested ImGui windows will be in dockspace
	{
		ImGui::Begin("Color Picker");

		Kure::Renderer2D::Statistics stats = Kure::Renderer2D::GetStats();
		ImGui::Text("Rendering Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);

		ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));


		ImGui::End();
	}


}
void Sandbox2D::OnEvent(Kure::Event& event) {
	KR_PROFILE_FUNCTION();
	m_CameraController->OnEvent(event);
}
