#include "jlhepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace JLHE {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			JLHE_CORE_ASSERT(false, "Renderer API None is not Supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}
		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not Supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(path);
		}
		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}