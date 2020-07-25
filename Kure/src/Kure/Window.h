#pragma once

#include "krpch.h"
#include "Kure/Core.h"
#include "Kure/Events/Event.h"

namespace Kure {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Kure Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	//interface for desktop based window
	//implementation inside Platform->[platform name] folders
	class KURE_API Window {
	public:

		using EventCallbackFn = std::function<void(Event&)>; //function that takes Event& as paramter, and returns void

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0; 
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps()); 
	};

}
