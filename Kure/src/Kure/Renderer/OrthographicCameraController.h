#pragma once

#include "Kure/Renderer/OrthographicCamera.h"
#include "Kure/Core/TimeStep.h"

#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Events/MouseEvent.h"


namespace Kure {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& event);
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		void SetZoom(float zoom) { m_ZoomLevel = zoom; CalculateView(); }
		float GetZoom() const { return m_ZoomLevel; }
	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraTranslation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };

		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;
	};


}

