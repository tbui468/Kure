#pragma once

#include <glm/glm.hpp>
#include "Kure/Core.h"

namespace Kure {

	//interface for orthographic and perspective camera
	class Camera {
	public:
		virtual glm::vec3 GetPosition() const = 0;
		virtual glm::vec3 GetOrientation() const = 0;
		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
		virtual void SetPosition(glm::vec3 position) = 0;
		virtual void SetOrientation(glm::vec3 orientation) = 0;
		virtual void CalculateViewProjectionMatrix() = 0;
		static Ref<Camera> Create(float left, float right, float bottom, float top, float n, float f); //defined in orthographic and perspective camera classes
	};

}
