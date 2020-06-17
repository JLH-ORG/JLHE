#pragma once

#include "RendererAPI.h"

namespace JLHE {

	class RenderCommand {
	public:
		inline static void Init() { s_RendererAPI->Init(); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		inline static void SetClearColour(const glm::vec4& colour) { s_RendererAPI->SetClearColour(colour); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const JLHE::Ref<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}