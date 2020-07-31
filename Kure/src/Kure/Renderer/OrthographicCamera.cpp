#include "krpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/projection.hpp"

namespace Kure {


	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, n, f)), m_Position(0.0f), m_Orientation(0.0f) {
		CalculateViewProjectionMatrix();
	}


	void OrthographicCamera::SetPosition(glm::vec3 position) {
		m_Position = position;
		CalculateViewProjectionMatrix();
	}
	void OrthographicCamera::SetOrientation(glm::vec3 orientation) {
		m_Orientation = orientation;
		CalculateViewProjectionMatrix();
	}

	void OrthographicCamera::CalculateViewProjectionMatrix() {
		m_ViewMatrix = glm::inverse(glm::rotate(glm::translate(glm::mat4(1.0f), m_Position), m_Orientation.z, glm::vec3(0.0f, 0.0f, 1.0f)));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
