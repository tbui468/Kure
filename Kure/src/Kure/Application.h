#pragma once

#include "Core.h"

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

