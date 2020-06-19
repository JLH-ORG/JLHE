#pragma once

#include <JLHE.h>

class Sandbox2D : public JLHE::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(JLHE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(JLHE::Event & e) override;
private:
	JLHE::OrthographicCameraController m_CameraController;

	// TEMPORARY
	JLHE::Ref<JLHE::VertexArray> m_SquareVA;
	JLHE::Ref<JLHE::Texture2D> m_CheckerboardTexture;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};