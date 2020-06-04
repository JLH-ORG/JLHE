#include "jlhepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace JLHE {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not supported");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not supported");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}