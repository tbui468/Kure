#include "krpch.h"
#include "Kure/Renderer/OrthographicCameraController.h"

#include "Kure/Core/Input.h"
#include "Kure/Core/KeyCodes.h"

namespace Kure {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel, 0.0f, 1.0f),
		m_Rotation(rotation)
	{

	}

	//handled keyboard inputs in OnUpdate for smooth interaction (at frame rate)
	void OrthographicCameraController::OnUpdate(TimeStep ts) {
		if (Kure::Input::IsKeyPressed(KR_KEY_A)) {
			m_CameraTranslation.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_D)) {
			m_CameraTranslation.x += m_CameraTranslationSpeed * ts;
		}
		if (Kure::Input::IsKeyPressed(KR_KEY_W)) {
			m_CameraTranslation.y += m_CameraTranslationSpeed * ts;
		}
		else if (Kure::Input::IsKeyPressed(KR_KEY_S)) {
			m_CameraTranslation.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation) {
			if (Kure::Input::IsKeyPressed(KR_KEY_Q)) {
				m_CameraRotation.z += m_CameraRotationSpeed * ts;
			}
			else if (Kure::Input::IsKeyPressed(KR_KEY_E)) {
				m_CameraRotation.z -= m_CameraRotationSpeed * ts;
			}
		}

		//skips rotation transformation
		if (!m_Rotation) {
			m_Camera.SetViewOnTranslation(m_CameraTranslation);
		}
		else {
			m_Camera.SetView(m_CameraTranslation, m_CameraRotation);
		}

	}

	//handled mouse scroll and window resize (doesn't need to be smooth, eg once a frame is enought)
	void OrthographicCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(KR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(KR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::CalculateView() {
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, 0.0f, 1.0f);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_CameraTranslationSpeed = m_ZoomLevel;
		CalculateView();
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& event) {
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		CalculateView();
		return false;
	}


}
