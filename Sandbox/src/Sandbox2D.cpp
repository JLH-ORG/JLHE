#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}


void Sandbox2D::OnAttach() {
	m_SquareVA = JLHE::VertexArray::Create();

	float squareVertices[5 * 4] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
	};

	JLHE::Ref<JLHE::VertexBuffer> squareVB = 
		JLHE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ JLHE::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	JLHE::Ref<JLHE::IndexBuffer> squareIB =
		JLHE::IndexBuffer::Create(squareIndices, sizeof(squareIndices));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = JLHE::Shader::Create("Assets/Shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(JLHE::Timestep ts) {
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	JLHE::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
	JLHE::RenderCommand::Clear();

	JLHE::Renderer::BeginScene(m_CameraController.GetCamera()); {
		
		std::dynamic_pointer_cast<JLHE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<JLHE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		JLHE::Renderer::Submit(m_SquareVA, m_FlatColorShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		JLHE::Renderer::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(JLHE::Event& e) {
	m_CameraController.OnEvent(e);
}