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
		EntityInQueue(const sf::Vector2f& startingPosition, std::string&& entityName)
			: m_startingPosition(startingPosition),
			m_entityName(std::move(entityName))
		{}
		
		const sf::Vector2f m_startingPosition;
		const std::string m_entityName;
	};

	class EntityFactory
	{
	public:
		EntityFactory();
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;

		std::unique_ptr<Entity> getEntity(const std::string& entityName, const sf::Vector2f& startingPosition, int entityID) const;

	private:
		std::unordered_map<std::string, std::function<std::unique_ptr<Entity>(const sf::Vector2f&, int)>> m_entityFactory;

		template <class T>
		void registerEntity(std::string&& name)
		{
			assert(m_entityFactory.find(name) == m_entityFactory.cend());
			m_entityFactory.emplace(std::move(name), [](const sf::Vector2f& startingPosition, int entityID) -> std::unique_ptr<T>
			{
				return std::make_unique<T>(startingPosition, entityID);
			});
		}
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	void addEntity(const sf::Vector2f& startingPosition, std::string&& entityName);
	void removeEntity(int entityID);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;

private:
	const EntityFactory m_entityFactory;
	std::vector<int> m_entityRemovals;
	std::deque<EntityInQueue> m_entityQueue;
	std::list<std::unique_ptr<Entity>> m_entities;
	int m_entityCounter; //ID for each entity

	void handleEntityQueue();
	void handleRemovals();
	void addEntityFromQueue(const EntityInQueue& entityInQueue);
};