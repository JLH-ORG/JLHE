#pragma once

namespace JLHE {

	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }
	private:
		bool m_Running = true;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(); // To be defined in CLIENT.

}