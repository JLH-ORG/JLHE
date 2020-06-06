#include <JLHE.h>

class ExampleLayer : public JLHE::Layer {
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
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

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new JLHE::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override {
		JLHE::RenderCommand::SetClearColour({ 1.0f, 0.5f, 0.5f, 1 });
		JLHE::RenderCommand::Clear();

		m_Camera.SetRotation(45.0f);

		JLHE::Renderer::BeginScene(m_Camera); {
			m_Shader->Bind();
			m_Shader->UploadUniformMat4("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
			JLHE::Renderer::Submit(m_VertexArray, m_Shader);
			JLHE::Renderer::EndScene();
		}

	}

private:
	std::shared_ptr<JLHE::VertexArray> m_VertexArray;
	std::shared_ptr<JLHE::Shader> m_Shader;

	JLHE::OrthographicCamera m_Camera;
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