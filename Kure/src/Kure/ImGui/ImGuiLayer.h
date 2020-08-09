#pragma once

#include "Kure/Core/Layer.h"

#include "Kure/Events/ApplicationEvent.h"
#include "Kure/Events/KeyEvent.h"
#include "Kure/Events/MouseEvent.h"

namespace Kure {

	class KURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnImGuiRender() override;
	
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

