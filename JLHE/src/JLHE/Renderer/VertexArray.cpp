#include "jlhepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace JLHE {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    
				JLHE_CORE_ASSERT(false, "Renderer API None is not Supported"); 
				return nullptr;
		case RendererAPI::API::OpenGL:  
				return std::make_shared<OpenGLVertexArray>();
		}
		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}