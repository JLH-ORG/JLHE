#include <JLHE.h>

class Sandbox : public JLHE::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

JLHE::Application* JLHE::CreateApplication() {
	return new Sandbox();
}