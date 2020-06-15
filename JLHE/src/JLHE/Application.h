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
		bool OnWindowResize(WindowResizeEvent& e);

		JLHE::Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		Timestep m_LastTime;

		static Application* s_Instance;
	};

	Application* CreateApplication(); // To be defined in CLIENT.

}