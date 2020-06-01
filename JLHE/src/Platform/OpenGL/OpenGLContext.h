#pragma once

#include "JLHE/Renderer/GraphicsContext.h"

// Forward Declaration
struct GLFWwindow;

namespace JLHE {

	class OpenGlContext : public GraphicsContext {
	public:
		OpenGlContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}