#include <JLHE.h>
#include <JLHE/Core/EntryPoint.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

#include "Sandbox2D.h"

// TEMPORARY
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public JLHE::Layer {
public:
	ExampleLayer() 
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true), m_TrianglePosition(0.0f) {
		m_VertexArray = JLHE::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		JLHE::Ref<JLHE::VertexBuffer> vertexBuffer;
		vertexBuffer = JLHE::VertexBuffer::Create(vertices, sizeof(vertices));
		JLHE::BufferLayout layout = {
			{ JLHE::ShaderDataType::Float3, "a_Position" },
			{ JLHE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		JLHE::Ref<JLHE::IndexBuffer> indexBuffer;
		indexBuffer = JLHE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
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

		m_Shader = JLHE::Shader::Create("Triangle", vertexSrc, fragmentSrc);

		//----------------------------------------------------------

		m_SquareVA = JLHE::VertexArray::Create();
		
		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		
		JLHE::Ref<JLHE::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = JLHE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		
		squareVertexBuffer->SetLayout({
			{ JLHE::ShaderDataType::Float3, "a_Position" },
			{ JLHE::ShaderDataType::Float2, "a_TexCoord" } 
		});
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);
		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		JLHE::Ref<JLHE::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = JLHE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIndexBuffer);
		
		//m_TextureShader = JLHE::Shader::Create("Assets/Shaders/Texture.glsl");
		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		m_Texture = JLHE::Texture2D::Create("Assets/Textures/Checkerboard.png");
		
		std::dynamic_pointer_cast<JLHE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<JLHE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(JLHE::Timestep timestep) override {
		m_CameraController.OnUpdate(timestep);

		JLHE::RenderCommand::SetClearColour({ m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, 255 });
		JLHE::RenderCommand::Clear();

		auto textureShader = m_ShaderLibrary.Get("Texture");

		JLHE::Renderer::BeginScene(m_CameraController.GetCamera()); {
			m_Texture->Bind();
			JLHE::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			
			JLHE::Renderer::Submit(m_VertexArray, m_Shader, glm::translate(glm::mat4(1.0f), m_TrianglePosition) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)));
	
			JLHE::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Clear Colour", glm::value_ptr(m_ClearColour));
		ImGui::End();
	}

	virtual void OnEvent(JLHE::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	JLHE::Ref<JLHE::VertexArray> m_VertexArray, m_SquareVA;
	JLHE::Ref<JLHE::Shader> m_Shader;

	JLHE::OrthographicCameraController m_CameraController;

	JLHE::Ref<JLHE::Texture2D> m_Texture;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_TrianglePosition;

	float m_TriangleMoveSpeed = 0.5f;

	JLHE::ShaderLibrary m_ShaderLibrary;

	glm::vec3 m_ClearColour = { 30, 30, 30 };
};

class Sandbox : public JLHE::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}

};

JLHE::Application* JLHE::CreateApplication() {
	return new Sandbox();
}