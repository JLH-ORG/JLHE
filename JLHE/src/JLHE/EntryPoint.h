#pragma once

#ifdef JLHE_PLATFORM_WINDOWS

	extern JLHE::Application* JLHE::CreateApplication();

	int main(int argc, char** argv) {
		JLHE::Log::Init();
		JLHE_CORE_TRACE("Initalized log.");

		auto app = JLHE::CreateApplication();
		app->Run();
		delete app;
	}

#endif