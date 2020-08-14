#pragma once

#include "Camera.h"

namespace Kure {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right , float bottom, float top, float n, float f);
		virtual ~OrthographicCamera() {}
		inline virtual glm::mat4 GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
		void SetProjection(float left, float right, float bottom, float top, float n, float f);
		void SetView(glm::vec3 translation, glm::vec3 rotation);
		void SetViewOnTranslation(glm::vec3 translation);
		virtual void CalculateViewProjectionMatrix() override;
	private:
		glm::mat4 m_ViewProjectionMatrix; 
		glm::mat4 m_ProjectionMatrix; 
		glm::mat4 m_ViewMatrix;
	};


}
