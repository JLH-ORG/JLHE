#include "jlhepch.h"
#include "Application.h"

namespace JLHE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

}