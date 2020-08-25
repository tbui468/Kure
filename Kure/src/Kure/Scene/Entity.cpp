#include "krpch.h"
#include "Entity.h"


namespace Kure {

	Entity::Entity(entt::entity entityHandle, Scene* scene) 
		: m_EntityHandle(entityHandle), m_Scene(scene) {
	}

}
