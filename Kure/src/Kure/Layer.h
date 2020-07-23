#pragma once

#include "Kure/Core.h"
#include "Kure/Events/Event.h"

namespace Kure {

	class KURE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {} //we should update every frame
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; //only for debug purposes since we shouldn't be accessing layers by name
		//can add enable/disable layer boolean (so it won't render/events will skip)
	};


}

