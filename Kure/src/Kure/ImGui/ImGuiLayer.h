#pragma once

#include "Kure/Layer.h"

namespace Kure {

	class KURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};

}

