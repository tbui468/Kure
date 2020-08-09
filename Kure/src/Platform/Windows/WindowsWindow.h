#pragma once

#include "Kure/Core/Window.h"
#include "Kure/Renderer/Context.h"

#include <GLFW/glfw3.h>


namespace Kure {


	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& prop);
		virtual ~WindowsWindow();
		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& prop);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window; 
		Context* m_Context;  //contexts are related to rendering

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallbackFn EventCallback;  //EventCallbackFn is defined (in Application constructor) to Application::OnEvent(Event& e)
		};

		WindowData m_Data;
	};


}

