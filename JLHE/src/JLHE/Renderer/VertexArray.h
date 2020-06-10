#pragma once

#include <memory>
#include "Buffer.h"

// TEMPORARY
#include <vector>

namespace JLHE {

	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const JLHE::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const JLHE::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<JLHE::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const JLHE::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}