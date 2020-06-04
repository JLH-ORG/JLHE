#pragma once

#ifdef JLHE_PLATFORM_WINDOWS

#include <glad/glad.h>

	extern JLHE::Application* JLHE::CreateApplication();

	int main(int argc, char** argv) {
		JLHE::Log::Init();
		JLHE_CORE_TRACE("Initalized log.");
		JLHE_CORE_TRACE("GL Version: {0}", glGetString(GL_VERSION));

		auto app = JLHE::CreateApplication();
		app->Run();
		delete app;
	}

#endif