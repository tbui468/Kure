#pragma once

#include "Kure/Renderer/Context.h"


struct GLFWwindow;

namespace Kure {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};


}
