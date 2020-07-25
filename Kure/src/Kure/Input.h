#pragma once

#include "Kure/Core.h"

namespace Kure {

	class KURE_API Input {
	public:
		static bool IsKeyPressed(int key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsMousePressed(int button) { return s_Instance->IsButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int key) const = 0; 
		virtual bool IsButtonPressedImpl(int button) const = 0; 
		virtual std::pair<float, float> GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
	private:
		static Input* s_Instance; //initialized in WindowsInput.cpp
	};

}
