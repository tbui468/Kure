#pragma once

#include "Core.h" //need this for KURE_API (which exports the class)
#include "Events/Event.h"

namespace Kure {

	class KURE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}

