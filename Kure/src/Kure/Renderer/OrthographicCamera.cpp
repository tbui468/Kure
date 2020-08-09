#include "krpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/projection.hpp"

namespace Kure {


	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, n, f)), m_ViewMatrix(0.0f) {
		CalculateViewProjectionMatrix();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float n, float f) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, n, f);
		CalculateViewProjectionMatrix();
	}


	void OrthographicCamera::SetView(glm::vec3 translation, glm::vec3 rotation) {
		m_ViewMatrix = glm::inverse(glm::rotate(glm::translate(glm::mat4(1.0f), translation), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)));
		CalculateViewProjectionMatrix();
	}

	void OrthographicCamera::CalculateViewProjectionMatrix() {
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
