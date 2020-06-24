 #include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) {}


void Sandbox2D::OnAttach() {
	JLHE_PROFILE_FUNCTION();

	m_CheckerboardTexture = JLHE::Texture2D::Create("Assets/Textures/Checkerboard.png");
	m_SubTexture = JLHE::SubTexture2D::CreateFromCoords(m_CheckerboardTexture, { 0, 0 }, { 8, 8 }, { 1, 2 });
}

void Sandbox2D::OnDetach() {
	JLHE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(JLHE::Timestep ts) {
	JLHE_PROFILE_FUNCTION();

	JLHE::Renderer2D::ResetStats();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	JLHE::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
	JLHE::RenderCommand::Clear();

	{
		JLHE_PROFILE_SCOPE("Render Draw");
		JLHE::Renderer2D::BeginScene(m_CameraController.GetCamera()); 
		JLHE::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.0f, 1.0f }, m_SquareColor);
		JLHE::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, 45.0f, m_SquareColor);
		JLHE::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 1.0f }, m_SquareColor);
		JLHE::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, 45.0f, m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
		JLHE::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		JLHE::Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 45.0f, m_CheckerboardTexture, 20.0f);
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				JLHE::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}

		JLHE::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.7f }, { 1, 2 }, m_SubTexture);
		JLHE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	JLHE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = JLHE::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(JLHE::Event& e) {
	m_CameraController.OnEvent(e);
}