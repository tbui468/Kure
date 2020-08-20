#pragma once

#include "Kure/Core/Core.h"

namespace Kure {

	class Input {
	public:
		static bool IsKeyPressed(int key);
		static bool IsMousePressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
