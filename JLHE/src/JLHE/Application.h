#pragma once
#include "JLHE/LayerStack.h"

namespace JLHE {

	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(); // To be defined in CLIENT.

}