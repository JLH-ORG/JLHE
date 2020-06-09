#include <JLHE.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

// TEMPORARY
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public JLHE::Layer {
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_TrianglePosition(0.0f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(JLHE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<JLHE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(JLHE::VertexBuffer::Create(vertices, sizeof(vertices)));

		JLHE::BufferLayout layout = {
			{ JLHE::ShaderDataType::Float3, "a_Position" },
			{ JLHE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<JLHE::IndexBuffer> indexBuffer;
		indexBuffer.reset(JLHE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(JLHE::Shader::Create(vertexSrc, fragmentSrc));


	}

	void OnUpdate(JLHE::Timestep timestep) override {

		if (JLHE::Input::IsKeyPressed(JLHE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

		if (JLHE::Input::IsKeyPressed(JLHE_KEY_J))
			m_TrianglePosition.x -= m_TriangleMoveSpeed * timestep;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_L))
			m_TrianglePosition.x += m_TriangleMoveSpeed * timestep;

		if (JLHE::Input::IsKeyPressed(JLHE_KEY_I))
			m_TrianglePosition.y += m_TriangleMoveSpeed * timestep;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_K))
			m_TrianglePosition.y -= m_TriangleMoveSpeed * timestep;
		
		if (JLHE::Input::IsKeyPressed(JLHE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		else if (JLHE::Input::IsKeyPressed(JLHE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		JLHE::RenderCommand::SetClearColour({ m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, 255 });
		JLHE::RenderCommand::Clear();

		JLHE::Renderer::BeginScene(m_Camera); {
			m_Shader->Bind();
			std::dynamic_pointer_cast<JLHE::OpenGLShader>(m_Shader)->UploadUniformMat4("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
			JLHE::Renderer::Submit(m_VertexArray, m_Shader, glm::translate(glm::mat4(1.0f), m_TrianglePosition));
			JLHE::Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)));
			JLHE::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Clear Colour", glm::value_ptr(m_ClearColour));
		ImGui::End();
	}

private:
	std::shared_ptr<JLHE::VertexArray> m_VertexArray;
	std::shared_ptr<JLHE::Shader> m_Shader;

	JLHE::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_TrianglePosition;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
	float m_TriangleMoveSpeed = 0.5f;

	glm::vec3 m_ClearColour = { 30, 30, 30 };
};

class Sandbox : public JLHE::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

};

JLHE::Application* JLHE::CreateApplication() {
	return new Sandbox();
}