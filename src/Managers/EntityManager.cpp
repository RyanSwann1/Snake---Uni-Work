#include <Managers\EntityManager.h>
#include <Components\ComponentDrawable.h>
#include <Components\ComponentSnake.h>

//Entity Factory
EntityManager::EntityFactory::EntityFactory()
	: m_entityFactory()
{

}

std::unique_ptr<Entity> EntityManager::EntityFactory::getEntity(const std::string & entityName, const sf::Vector2f& startingPosition, int entityID) const
{
	auto iter = m_entityFactory.find(entityName);
	assert(iter != m_entityFactory.cend());
	return iter->second(startingPosition, entityID);
}

//Entity Manager
EntityManager::EntityManager()
	: m_entityFactory()
{}

void EntityManager::addEntity(const sf::Vector2f & startingPosition, std::string&& entityName)
{
	m_entityQueue.emplace_back(startingPosition, std::move(entityName));
}

void EntityManager::removeEntity(int entityID)
{
	auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityID](const auto& entity) { return entity->getID() == entityID; });
	assert(iter != m_entities.end());
	m_entityRemovals.push_back(iter->get()->getID());
}

void EntityManager::update(float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}

	handleEntityQueue();
	handleRemovals();
}

void EntityManager::draw(sf::RenderWindow & window) const
{
	for (const auto& entity : m_entities)
	{
		entity->draw(window);
	}
}

void EntityManager::handleEntityQueue()
{
	for (const auto& entityInQueue : m_entityQueue)
	{
		addEntityFromQueue(entityInQueue);
	}

	m_entityQueue.clear();
}

void EntityManager::handleRemovals()
{
	for (auto entityIDToRemove : m_entityRemovals)
	{
		auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityIDToRemove]
		(const auto& entity) { return entity->getID() == entityIDToRemove; });
		assert(iter != m_entities.cend());

		m_entities.erase(iter);
	}

	m_entityRemovals.clear();
}

void EntityManager::addEntityFromQueue(const EntityInQueue& entityInQueue)
{
	auto newEntity = m_entityFactory.getEntity(entityInQueue.m_entityName, entityInQueue.m_startingPosition, m_entityCounter);
	++m_entityCounter;
	m_entities.push_back(std::move(newEntity));
}