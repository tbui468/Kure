#include "krpch.h"
#include "OpenGLContext.h"

#include "Kure/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Kure {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle){
		KR_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KR_CORE_ASSERT(status, "Failed to initialize glad");

		//check opengl vendor, driver, etc
		KR_CORE_INFO("OpenGL info:");
		KR_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		KR_CORE_INFO("Rendere: {0}", glGetString(GL_RENDERER));
		KR_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}
