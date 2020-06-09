#include "jlhepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JLHE {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: JLHE_CORE_ASSERT(false, "Renderer API None is not Supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
			return nullptr;
	}

}