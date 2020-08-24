#pragma once

#include <Kure.h>
#include "entt.hpp"

namespace Kure {


	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		entt::entity CreateEntity();
		void OnUpdate(TimeStep ts);

		//TEMP
		entt::registry& Reg() { return m_Registry; }

	private:
		entt::registry m_Registry;
	};


}

