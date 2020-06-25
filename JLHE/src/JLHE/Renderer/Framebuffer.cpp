#include "jlhepch.h"
#include "Framebuffer.h"

#include "JLHE/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace JLHE {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    
				JLHE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return CreateRef<OpenGLFramebuffer>(spec);
		}
		JLHE_CORE_ASSERT(false, "Unknown Render API");
		return nullptr;
	}
}