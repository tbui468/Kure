#include "krpch.h"
#include "OpenGLContext.h"

#include "Kure/Core/Log.h"

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

		#ifdef KR_ENABLE_ASSERTS
				int versionMajor;
				int versionMinor;

				glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
				glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
			KR_CORE_ASSERT(versionMajor > 4 || versionMajor == 4 && versionMinor >= 5, "Kure requires at least OpenGL version 4.5!")
		#endif
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}
