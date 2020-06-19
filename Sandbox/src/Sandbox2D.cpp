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
}

void Sandbox2D::OnDetach() {
	JLHE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(JLHE::Timestep ts) {
	JLHE_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	JLHE::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1.0f });
	JLHE::RenderCommand::Clear();

	{
		JLHE_PROFILE_SCOPE("Render Draw");
		JLHE::Renderer2D::BeginScene(m_CameraController.GetCamera()); 
		JLHE::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.0f, 1.0f }, m_SquareColor);
		JLHE::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, glm::radians(-45.0f), m_SquareColor);
		JLHE::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 1.0f }, m_SquareColor);
		JLHE::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
		JLHE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	JLHE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(JLHE::Event& e) {
	m_CameraController.OnEvent(e);
}