#pragma once

#include "RenderCommand.h"

#include "JLHE/Renderer/OrthographicCamera.h"
#include "JLHE//Renderer/Shader.h"

namespace JLHE {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const JLHE::Ref<VertexArray>& vertexArray, const JLHE::Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}
