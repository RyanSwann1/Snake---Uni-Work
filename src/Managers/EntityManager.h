#pragma once

#include <functional>
#include <Entity\Entity.h>
#include <Components\ComponentType.h>
#include <list>
#include <unordered_map>
#include <string>
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
		EntityInQueue(const sf::Vector2f& startingPosition, std::string&& entityName, EntityTag entityTag)
			: m_startingPosition(startingPosition),
			m_entityName(std::move(entityName)),
			m_entityTag(entityTag)
		{}
		
		const sf::Vector2f m_startingPosition;
		const std::string m_entityName;
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
	
		std::vector<ComponentType> getEntityComponents(const std::string& entityName) const;

	private:
		std::unordered_map<std::string, std::vector<ComponentType>> m_entityComponentFactory;
	
		void registerEntityComponents(std::string&& entityName, std::vector<ComponentType>&& entityComponents);
	};

	class EntityFactory
	{
	public:
		EntityFactory();
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;

		Entity getEntity(const std::string& entityName, int entityID, EntityTag entityTag) const;

	private:
		std::unordered_map<std::string, std::function<Entity(int, EntityTag)>> m_entityFactory;

		void registerEntity(std::string&& name);
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	void addEntity(const sf::Vector2f& startingPosition, std::string&& entityName, EntityTag entityTag);
	void removeEntity(int entityID);

	void update(float deltaTime);

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

	template <class Component>
	Component& getEntityComponent(Entity& entity, ComponentType componentType)
	{
		assert(entity.m_components[static_cast<int>(componentType)].get());
		return *static_cast<Component*>(entity.m_components[static_cast<int>(componentType)].get());
	}
};