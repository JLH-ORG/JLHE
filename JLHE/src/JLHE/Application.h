#pragma once

#include "Core.h"

#include "JLHE/Window.h"
#include "JLHE/LayerStack.h"
#include "JLHE/Events/Event.h"
#include "JLHE/Events/ApplicatonEvent.h"

#include "JLHE/ImGui/ImGuiLayer.h"
#include "JLHE/Renderer/Buffer.h"

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

		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(); // To be defined in CLIENT.

}