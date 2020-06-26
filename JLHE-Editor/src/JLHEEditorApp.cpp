#include <JLHE.h>
#include <JLHE/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace JLHE {

	class Sandbox : public Application {
	public:
		Sandbox() {
			PushLayer(new EditorLayer());
		}

		~Sandbox() {

		}

	};

	Application* CreateApplication() {
		return new Sandbox();
	}
}