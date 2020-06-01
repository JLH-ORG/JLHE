#include "jlhepch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace JLHE {

	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle) {
		// TODO: Validation of m_WindowHandle
		JLHE_CORE_ASSERT(windowHandle, "Window Handle is Null")
	}

	void OpenGlContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JLHE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGlContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}

