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

		}
	}

}