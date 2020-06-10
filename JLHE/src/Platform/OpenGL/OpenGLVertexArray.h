#pragma once

#include "JLHE/Renderer/VertexArray.h"

namespace JLHE {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const JLHE::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const JLHE::Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<JLHE::Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const JLHE::Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<JLHE::Ref<VertexBuffer>> m_VertexBuffers;
		JLHE::Ref<IndexBuffer> m_IndexBuffer;
	};

}