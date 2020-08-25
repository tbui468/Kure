#include "krpch.h"
#include "Scene.h"
#include "Kure/Scene/Components.h"
#include "Kure/Renderer/Renderer2D.h"

#include "glm/glm.hpp"


namespace Kure {

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity) {
		//do stuff here
	}

	Scene::Scene() {

		/* ENTT Example code

		struct TransformComponent {
			glm::mat4 Transform;
			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform) : Transform(transform) {}
			operator glm::mat4& () { return Transform; } //???
			operator const glm::mat4& () const { return Transform; } //???
		};

		struct MeshComponent {
			float Value;
			MeshComponent() = default;
		};

		entt::entity entity = m_Registry.create(); //creates new entity
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f)); //adds component to entity

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if(m_Registry.has<TransformComponent>(entity)) //checks if component is part of entity
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity); //gets component of entity


		//get all entities with transfromComponent
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view) {
			TransformComponent& transform = view.get<TransformComponent>(entity); //gets component of entity
		}

	
		//get multiple components
		
		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group) {
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
			//do stuff with transfrom and mesh (eg Submit to renderer)
		}*/
	}


	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
		TagComponent& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}


	void Scene::OnUpdate(TimeStep ts) {
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group) {
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}


}
