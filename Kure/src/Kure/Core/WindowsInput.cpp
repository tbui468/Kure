#include "krpch.h"
#include "Kure/Core/Input.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Kure {

	

	bool Input::IsKeyPressed(int keycode) {

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT; 
	}


	bool Input::IsMousePressed(int button) {

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}


	std::pair<float, float> Input::GetMousePosition() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);

		return std::make_pair<float, float>(float(x), float(y));
	}

	float Input::GetMouseX() {
		return GetMousePosition().first;
	}

	float Input::GetMouseY() {
		return GetMousePosition().second;
	}


}
