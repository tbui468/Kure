#pragma once

#include <Kure.h>
#include "entt.hpp"

namespace Kure {

	class Entity;
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() {}
		Entity CreateEntity(const std::string& name = std::string());
		void OnUpdate(TimeStep ts);

	private:
		entt::registry m_Registry;
		friend class Entity; 
	};


}

