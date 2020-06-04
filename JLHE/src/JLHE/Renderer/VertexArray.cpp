#include "jlhepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace JLHE {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:    
				JLHE_CORE_ASSERT(false, "Renderer API None is not Supported"); 
				return nullptr;
			case RendererAPI::OpenGL:  
				return new OpenGLVertexArray();
		}
		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}