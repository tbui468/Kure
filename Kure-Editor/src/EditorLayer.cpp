#include "EditorLayer.h"


namespace Kure {

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



	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(CreateRef<OrthographicCameraController>(1280.0f / 720.0f, false)) {
		KR_PROFILE_FUNCTION();
	}


	void EditorLayer::OnAttach() {
		KR_PROFILE_FUNCTION();
		m_Texture = Texture2D::Create("assets/textures/texture.png");
		m_SpriteSheet = Texture2D::Create("assets/game/RPGpack_sheet_2X.png");
		m_SquaresTexture = Texture2D::Create("assets/textures/squaresTexture.png");

		//m_TreeSubTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, 2, 1, { 128.0f, 128.0f }, { 1.0f, 2.0f });
		m_BarrelSubTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, 9, 0, { 128.0f, 128.0f });
		m_GrassSubTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, 1, 11, { 128.0f, 128.0f });
		m_DirtSubTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, 6, 11, { 128.0f, 128.0f });
		m_WaterSubTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, 11, 11, { 128.0f, 128.0f });

		m_TextureMap['W'] = m_WaterSubTexture;
		m_TextureMap['D'] = m_DirtSubTexture;
		m_TextureMap['G'] = m_GrassSubTexture;

		m_CameraController->SetZoom(5.0f);

		FrameBufferSpecification frameBufferSpec;
		frameBufferSpec.Width = 1280;
		frameBufferSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(frameBufferSpec);
	}

	void EditorLayer::OnDetach() {
		KR_PROFILE_FUNCTION();
	}
	void EditorLayer::OnUpdate(TimeStep ts) {
		KR_PROFILE_FUNCTION();

		{
			KR_PROFILE_SCOPE("Camera Controller Onupdate()");
			m_CameraController->OnUpdate(ts);
			m_FrameBuffer->Bind();
		}

		{
			KR_PROFILE_SCOPE("Clear Buffer");
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
			Renderer2D::ResetStats();
		}


#if 0
		{
			KR_PROFILE_SCOPE("Begin scene setup");
			Renderer2D::BeginScene(m_CameraController->GetCamera());
		}
		{
			KR_PROFILE_SCOPE("Render 3 quads"); //negative z is further away from camera (0 is at camera)
			Renderer2D::DrawRotatedQuad({ 0.0f, -0.5f , -0.8f }, glm::radians(45.0f), { 1.0f, 1.0f }, m_Color);
			Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f , -0.5f }, glm::radians(60.0f), { 1.0f, 1.0f }, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
			Renderer2D::DrawQuad({ -0.7f, -0.1f }, { 2.0f, 0.8f }, { 0.5f, 0.2f, 0.8f, 1.0f });
			Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f, -0.1f }, glm::radians(180.0f), { 1.0f, 1.0f }, m_Texture, 2.0f, glm::vec4(1.0f, 0.3f, 0.3f, 1.0f));
			Renderer2D::DrawQuad({ 0.0f, 0.0f, -.9f }, { 10.0f, 10.0f }, m_Texture, 1.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));
			/*
			Renderer2D::DrawQuad({ 0.7f, 0.1f }, { 1.0f, 1.0f }, { 0.5f, 0.8f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ -0.5f, 0.5f, -.1f }, { 1.0f, 1.0f }, m_Texture, 12.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));
			Renderer2D::DrawQuad({ -0.5f, -1.0f, -.1f }, { 1.0f, 1.0f }, m_SquaresTexture, 2.0f, glm::vec4(0.3f, 1.0f, 0.3f, 1.0f));*/


			for (int i = -50; i < 50; ++i) {
				for (int j = -50; j < 50; ++j) {
					Renderer2D::DrawQuad({ (float)i, (float)j }, { 0.9f, 0.9f }, { ((float)i + 50.0f) / 100.0f, 0.2f, ((float)j + 50.0f) / 100.0f, 0.5f });
				}
			}
		}
		{
			KR_PROFILE_SCOPE("End scene");
			Renderer2D::EndScene();
		}
#endif
		Renderer2D::BeginScene(m_CameraController->GetCamera());
		//		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_SpriteSheet, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//		Renderer2D::DrawQuad({ 1.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_GrassSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_DirtSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		for (int32_t row = 0; row < mapWidth; ++row) {
			for (int32_t col = 0; col < mapHeight; ++col) {
				//get correct char c from s_MapTiles
				//get subtexture t from m_TextureMap using c
				//draw quad with subtexture t with 
				char c = s_MapTiles[col + (mapHeight - 1 - row) * mapWidth];
				Ref<SubTexture2D> texture;
				if (m_TextureMap.find(c) != m_TextureMap.end()) {
					texture = m_TextureMap[c];
				}
				else {
					texture = m_BarrelSubTexture;
				}

				Renderer2D::DrawQuad({ col - 12, row - 12, -0.1f }, { 1.0f, 1.0f }, texture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}



		//		Renderer2D::DrawRotatedQuad({ 1.0f, 1.0f, -0.1f }, glm::radians(45.0f), { 1.0f, 2.0f }, m_TreeSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//		Renderer2D::DrawRotatedQuad({ 0.0f, 1.5f, -0.1f }, glm::radians(180.0f), { 1.0f, 1.0f }, m_BarrelSubTexture, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer2D::EndScene();
		m_FrameBuffer->Unbind();



		//	dynamic_cast<OpenGLShader*>(m_FlatShader.get())->UploadUniformFloat4(m_Color, "u_Color");  //upload color
		//	m_Texture->Bind(0);  //texture slots and uniforms are not workint correctly
		//	Renderer::Submit(*m_VertexArray, glm::mat4(1.0f), *m_TextureShader);

	}
	void EditorLayer::OnImGuiRender() {

		KR_PROFILE_FUNCTION();


		bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


		//Panels inside dockspace
		{
			ImGui::Begin("Color Picker");
			Renderer2D::Statistics stats = Renderer2D::GetStats();
			ImGui::Text("Rendering Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quad Count: %d", stats.QuadCount);
			ImGui::ColorEdit4("Square color", glm::value_ptr(m_Color));
			ImGui::End();


			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
		
			//change frambuffersize, and projection matrix on resize
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != *(glm::vec2*) &viewportSize) { //this is dangerous!!!
				m_ViewportSize = { viewportSize.x, viewportSize.y };
				m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_CameraController->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			}

			//draw texture to Imgui panel
			uint32_t texture = m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image((ImTextureID)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

			ImGui::End();
			ImGui::PopStyleVar();


		}

		ImGui::End();

	}
	void EditorLayer::OnEvent(Event& event) {
		KR_PROFILE_FUNCTION();
		m_CameraController->OnEvent(event);
	}

}
