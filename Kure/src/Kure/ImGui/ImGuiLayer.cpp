#include "krpch.h"

#include "ImGuiLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/imguiOpenGLRenderer.h"


#include "Kure/Application.h"

//TEMPORARY - REMOVE LATER
#include <GLFW/glfw3.h> 
#include <glad/glad.h>


namespace Kure {


	ImGuiLayer::ImGuiLayer() :Layer("ImGuiLayer") {

	}
	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {


		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// Setup back-end capabilities flags
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)

		//TEMPORARY
		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

/*
		io.SetClipboardTextFn = ImGuiLayer::SetClipboard;
		io.GetClipboardTextFn = ImGuiLayer::GetClipboard;
		io.ClipboardUserData = (void*)(&Application::Get().GetWindow());*/


		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {
	}

	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
		dispatcher.Dispatch<MouseButtonPressedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<KeyPressedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(KR_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));

		//log event
		KR_CORE_TRACE("ImGuiLayer OnEvent: {0}", event);

	}
	

	///////////////////////////////////////////////IMGUI EVENTS///////////////////////////////////////
	//application (window) events
	bool ImGuiLayer::OnWindowResized(WindowResizedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());

		//
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}
	//mouse events
	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
		return false;
	}
	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += event.GetYOffset();
		io.MouseWheelH += event.GetXOffset();
		return false;
	}
	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;
		return false; //allow lower layers to process button click for now
	}
	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;
		return false; 
	}
	//key events
	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		//check for mods
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(event.GetKeyCode());
		return false;
	}

/*
	const char* ImGuiLayer::GetClipboard(void* user_data)
	{
		return glfwGetClipboardString((GLFWwindow*)user_data);
	}

	void ImGuiLayer::SetClipboard(void* user_data, const char* text)
	{
		glfwSetClipboardString((GLFWwindow*)user_data, text);
	}*/

}
