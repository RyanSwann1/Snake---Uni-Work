#include <Systems\SystemSnake.h>
#include <Managers\EntityManager.h>
#include <Locators\EntityManagerLocator.h>
#include <Components\ComponentSnake.h>
#include <Systems\SystemMessage.h>

SystemSnake::SystemSnake(SystemManager& systemManager, SystemType systemType)
	: SystemBase(systemManager, systemType)
{}

void SystemSnake::update() const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (SystemBase::entityHasComponent(entity, ComponentType::Snake))
		{
			continue;
		}

		handleSnakeMovement(entity, entityManager);
	}
}

void SystemSnake::onSystemMessage(const SystemMessage & systemMessage) const
{
	switch (systemMessage.m_systemEvent)
	{
	case SystemEvent::ExtendSnake :
	{
		extendSnake(*systemMessage.m_entity);
		break;
	}
	}
}

void SystemSnake::handleSnakeMovement(Entity& entity, EntityManager& entityManager) const
{
	//https://www.youtube.com/watch?v=zXg1mEVwpIw
	auto& snakeComponent = entityManager.getEntityComponent<ComponentSnake>(entity, ComponentType::Snake);
	if (snakeComponent.m_snake.size() == 1)
	{
		return;
	}

	auto newPosition = snakeComponent.m_snake.front()->m_oldPosition;
	for (auto iter = snakeComponent.m_snake.begin() + 1; iter != snakeComponent.m_snake.end(); ++iter)
	{
		iter->get()->m_position = newPosition;
		newPosition = iter->get()->m_oldPosition;
	}
}

void SystemSnake::extendSnake(Entity & entity) const
{
	auto& entityManager = EntityManagerLocator::get();
	auto& componentSnake = entityManager.getEntityComponent<ComponentSnake>(entity, ComponentType::Snake);

	const sf::Vector2f& spawnPosition = componentSnake.m_snake.back()->m_oldPosition;
	componentSnake.m_snake.push_back(std::make_unique<ComponentPosition>(ComponentType::Position));
	componentSnake.m_snake.back()->m_position

	entityManager.addEntity(spawnPosition, EntityName::SnakeTail, EntityTag::SnakeTail);
}