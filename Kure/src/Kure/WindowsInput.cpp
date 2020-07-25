#include "krpch.h"
#include "WindowsInput.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Kure {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) const {

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT; 
	}


	bool WindowsInput::IsButtonPressedImpl(int button) const {

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}


	std::pair<float, float> WindowsInput::GetMousePositionImpl() const {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);

		return std::make_pair<float, float>(float(x), float(y));
	}
	float WindowsInput::GetMouseXImpl() const {
		return GetMousePositionImpl().first;
	}
	float WindowsInput::GetMouseYImpl() const {
		return GetMousePositionImpl().second;
	}


}
