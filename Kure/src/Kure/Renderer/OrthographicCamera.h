#pragma once

#include "Camera.h"

namespace Kure {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right , float bottom, float top, float n, float f);
		virtual ~OrthographicCamera() {}
		inline virtual glm::vec3 GetPosition() const override { return m_Position; }
		inline virtual glm::vec3 GetOrientation() const override { return m_Orientation; }
		inline virtual glm::mat4 GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
		virtual void SetPosition(glm::vec3 position) override;
		virtual void SetOrientation(glm::vec3 orientation) override;
		virtual void CalculateViewProjectionMatrix() override;
	private:
		glm::mat4 m_ViewProjectionMatrix; //needs to be recalculated everytime one or the other changes
		glm::mat4 m_ProjectionMatrix; 
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Orientation;
	};


}
