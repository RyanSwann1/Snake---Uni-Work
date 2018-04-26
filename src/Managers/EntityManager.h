#pragma once

#include <functional>
#include <Entity\Entity.h>
#include <Entity\EntityName.h>
#include <Components\ComponentType.h>
#include <list>
#include <unordered_map>
#include <vector>
#include <SFML\Graphics.hpp>
#include <utility>
#include <deque>
#include <assert.h>
#include <memory>

class EntityManager
{
	class EntityInQueue
	{
	public:
		EntityInQueue(const sf::Vector2f& startingPosition, EntityName entityName, EntityTag entityTag)
			: m_startingPosition(startingPosition),
			m_entityName(std::move(entityName)),
			m_entityTag(entityTag)
		{}
		
		const sf::Vector2f m_startingPosition;
		const EntityName m_entityName;
		const EntityTag m_entityTag;
	};

	class ComponentFactory
	{
	public:
		ComponentFactory();
		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory& operator=(const ComponentFactory&) = delete;
		ComponentFactory(ComponentFactory&&) = delete;
		ComponentFactory&& operator=(ComponentFactory&&) = delete;

		std::unique_ptr<ComponentBase> getComponent(ComponentType type) const;

	private:
		std::unordered_map<ComponentType, std::function<std::unique_ptr<ComponentBase>()>> m_componentFactory;

		template <class Component>
		void registerComponent(ComponentType type)
		{
			assert(m_componentFactory.find(type) == m_componentFactory.cend());
			m_componentFactory.emplace(type, [type]() -> std::unique_ptr<Component>
			{
				return std::make_unique<Component>(type);
			});
		}
	};

	class EntityComponentFactory
	{
	public:
		EntityComponentFactory();
		EntityComponentFactory(const EntityComponentFactory&) = delete;
		EntityComponentFactory& operator=(const EntityComponentFactory&) = delete;
		EntityComponentFactory(EntityComponentFactory&&) = delete;
		EntityComponentFactory&& operator=(EntityComponentFactory&&) = delete;
	
		std::vector<ComponentType> getEntityComponents(EntityName entityName) const;

	private:
		std::unordered_map<EntityName, std::vector<ComponentType>> m_entityComponentFactory;
	
		void registerEntityComponents(EntityName entityName, std::vector<ComponentType>&& entityComponents);
	};

	class EntityFactory
	{
	public:
		EntityFactory();
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;

		Entity getEntity(EntityName entityName, int entityID, EntityTag entityTag) const;

	private:
		std::unordered_map<EntityName, std::function<Entity(int, EntityTag)>> m_entityFactory;

		void registerEntity(EntityName entityName);
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	template <class Component>
	Component& getEntityComponent(const Entity& entity, ComponentType componentType) const
	{
		assert(entity.m_components[static_cast<int>(componentType)].get());
		auto& component = entity.m_components[static_cast<int>(componentType)];
		return *static_cast<Component*>(component.get());
	}

	std::list<Entity>& getEntities() { return m_entities; }
	void addEntity(const sf::Vector2f& startingPosition, EntityName entityName, EntityTag entityTag);
	void removeEntity(int entityID);

	void update();

private:
	const ComponentFactory m_componentFactory;
	const EntityComponentFactory m_entityComponentFactory;
	const EntityFactory m_entityFactory;
	std::vector<int> m_entityRemovals;
	std::deque<EntityInQueue> m_entityQueue;
	std::list<Entity> m_entities;
	int m_entityCounter; //ID for each entity

	void handleEntityQueue();
	void handleRemovals();
	void addEntityFromQueue(const EntityInQueue& entityInQueue);
};