#pragma once

#include "jlhepch.h"
#include "JLHE/Core/Core.h"

namespace JLHE {

	class Input {
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);

		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}