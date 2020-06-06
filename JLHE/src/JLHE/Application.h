#pragma once

#include "Core.h"

#include "JLHE/Window.h"
#include "JLHE/LayerStack.h"
#include "JLHE/Events/Event.h"
#include "JLHE/Events/ApplicatonEvent.h"

#include "JLHE/ImGui/ImGuiLayer.h"
#include "JLHE/Renderer/Buffer.h"
#include "JLHE/Renderer/Shader.h"
#include "JLHE/Renderer/VertexArray.h"
#include "JLHE/Renderer/OrthographicCamera.h"

namespace JLHE {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		// Test
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		// End Test

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(); // To be defined in CLIENT.

}