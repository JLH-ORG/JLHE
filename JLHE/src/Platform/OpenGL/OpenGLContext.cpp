#include "jlhepch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace JLHE {

	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		JLHE_CORE_ASSERT(windowHandle, "Window Handle is Null")
	}

	void OpenGlContext::Init() {
		JLHE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JLHE_CORE_ASSERT(status, "Failed to initialize Glad!");
		JLHE_CORE_TRACE("Intialised Glad");
		JLHE_CORE_INFO("OpenGL Info:");
		JLHE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		JLHE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		JLHE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGlContext::SwapBuffers() {
		JLHE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}

