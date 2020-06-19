#pragma once

#ifdef JLHE_PLATFORM_WINDOWS

	extern JLHE::Application* JLHE::CreateApplication();

	int main(int argc, char** argv) {
		JLHE::Log::Init();

		JLHE_PROFILE_BEGIN_SESSION("Startup", "JLHE-Profile-Startup.json");
		auto app = JLHE::CreateApplication();
		JLHE_PROFILE_END_SESSION();

		JLHE_PROFILE_BEGIN_SESSION("Runtime", "JLHE-Profile-Runtime.json");
		app->Run();
		JLHE_PROFILE_END_SESSION();

		JLHE_PROFILE_BEGIN_SESSION("Shutdown", "JLHE-Profile-Shutdown.json");
		delete app;
		JLHE_PROFILE_END_SESSION();
	}

#endif