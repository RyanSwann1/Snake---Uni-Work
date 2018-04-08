#include <Managers\EntityManager.h>
#include <Components\ComponentDrawable.h>
#include <Components\ComponentSnake.h>
#include <Components\ComponentPosition.h>

//Component Factory
EntityManager::ComponentFactory::ComponentFactory()
{
	registerComponent<ComponentDrawable>(ComponentType::Drawable);
	registerComponent<ComponentPosition>(ComponentType::Position);
	registerComponent<ComponentSnake>(ComponentType::Snake);
}

std::unique_ptr<ComponentBase> EntityManager::ComponentFactory::getComponent(ComponentType type) const
{
	auto iter = m_componentFactory.find(type);
	assert(iter != m_componentFactory.cend());
	return iter->second();
}

//Entity Components Factory
EntityManager::EntityComponentFactory::EntityComponentFactory()
{
	//Register entity components
	registerEntityComponents("Snake", { ComponentType::Player });

}

std::vector<ComponentType> EntityManager::EntityComponentFactory::getEntityComponents(const std::string & entityName) const
{
	const auto entityComponents = m_entityComponentFactory.find(entityName);
	assert(entityComponents != m_entityComponentFactory.cend());
	return entityComponents->second;
}

void EntityManager::EntityComponentFactory::registerEntityComponents(std::string && entityName, std::vector<ComponentType>&& entityComponents)
{
	assert(m_entityComponentFactory.find(entityName) == m_entityComponentFactory.cend());
	m_entityComponentFactory.emplace(std::move(entityName), std::move(entityComponents));
}

//Entity Factory
EntityManager::EntityFactory::EntityFactory()
	: m_entityFactory()
{

}

Entity EntityManager::EntityFactory::getEntity(const std::string & entityName, int entityID, EntityTag entityTag) const
{
	auto iter = m_entityFactory.find(entityName);
	assert(iter != m_entityFactory.cend());
	return iter->second(entityID, entityTag);
}

void EntityManager::EntityFactory::registerEntity(std::string && name)
{
	assert(m_entityFactory.find(name) == m_entityFactory.cend());
	m_entityFactory.emplace(std::move(name), [](int ID, EntityTag tag) -> Entity
	{
		return Entity(ID, tag);
	});
}

//Entity Manager
EntityManager::EntityManager()
	: m_componentFactory(),
	m_entityComponentFactory(),
	m_entityFactory(),
	m_entityRemovals(),
	m_entityQueue(),
	m_entities(),
	m_entityCounter(0)
{}

void EntityManager::addEntity(const sf::Vector2f & startingPosition, std::string&& entityName, EntityTag entityTag)
{
	m_entityQueue.emplace_back(startingPosition, std::move(entityName), entityTag);
}

void EntityManager::removeEntity(int entityID)
{
	auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityID](const auto& entity) { return entity.m_ID == entityID; });
	assert(iter != m_entities.end());
	m_entityRemovals.push_back(iter->m_ID);
}

void EntityManager::update(float deltaTime)
{
	handleEntityQueue();
	handleRemovals();
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
		(const auto& entity) { return entity.m_ID == entityIDToRemove; });
		assert(iter != m_entities.cend());

		m_entities.erase(iter);
	}

	m_entityRemovals.clear();
}

//class Entity
//{
//public:
//	Entity(int ID, EntityTag tag)
//		: m_ID(ID),
//		m_tag(tag)
//	{}
//
//	const int m_ID;
//	const EntityTag m_tag;
//	std::array<std::unique_ptr<ComponentBase>, static_cast<size_t>(ComponentType::Total)> m_components;
//};
//
//class EntityFactory
//{
//public:
//	EntityFactory();
//	EntityFactory(const EntityFactory&) = delete;
//	EntityFactory& operator=(const EntityFactory&) = delete;
//	EntityFactory(EntityFactory&&) = delete;
//	EntityFactory&& operator=(EntityFactory&&) = delete;
//
//	Entity getEntity(const std::string& entityName, int entityID, EntityTag entityTag) const;
//
//private:
//	std::unordered_map<std::string, std::function<Entity(int, EntityTag)>> m_entityFactory;
//
//	void registerEntity(std::string&& name);
//};



void EntityManager::addEntityFromQueue(const EntityInQueue& entityInQueue)
{
	const auto entityComponentTypes = m_entityComponentFactory.getEntityComponents(entityInQueue.m_entityName);
	auto entity = m_entityFactory.getEntity(entityInQueue.m_entityName, m_entityCounter, entityInQueue.m_entityTag);
	//Assign entity components
	for (const auto componentType : entityComponentTypes)
	{
		entity.m_components[static_cast<int>(componentType)] = m_componentFactory.getComponent(componentType);
	}
	
	//Initialize entity starting position
	getEntityComponent<ComponentPosition>(entity, ComponentType::Position).m_position = entityInQueue.m_startingPosition;

	//Add new entity
	m_entities.push_back(std::move(entity));
}
