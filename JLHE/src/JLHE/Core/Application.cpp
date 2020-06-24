#include "jlhepch.h"
#include "Application.h"

#include "JLHE/Core/Log.h"

#include <glad/glad.h>
#include "JLHE/Renderer/Renderer.h"

#include "JLHE/Core/Input.h"

#include "JLHE/Core/Random.h"

#include <GLFW/glfw3.h>

namespace JLHE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_LastTime(0.0f) {
		JLHE_PROFILE_FUNCTION();

		JLHE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = JLHE::Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Random::Init();
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		JLHE_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		JLHE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		JLHE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		JLHE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		JLHE_PROFILE_FUNCTION();

		while (m_Running) {
			float time = glfwGetTime();
			Timestep timestep = time - m_LastTime;
			m_LastTime = time;
			
			if (!m_Minimized) {
				JLHE_PROFILE_SCOPE("Updating Layers")
				for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);
			}

			{
				JLHE_PROFILE_SCOPE("LayerStack OnImGUIRender");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		JLHE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}