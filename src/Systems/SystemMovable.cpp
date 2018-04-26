#include <systems\SystemMovable.h>
#include <Locators\EntityManagerLocator.h>
#include <Managers\EntityManager.h>
#include <Components\ComponentMovable.h>
#include <Components\ComponentPosition.h>
#include <Locators\GameLogicLocator.h>
#include <Game\GameLogic.h>
#include <Systems\SystemMessage.h>
#include <iostream>

//System Movable
SystemMovable::SystemMovable(SystemManager & systemManager, SystemType systemType)
	: SystemBase(systemManager, systemType)
{

}

void SystemMovable::update() const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (!SystemBase::entityHasComponent(entity, ComponentType::Movable))
		{
			continue;
		}
		
		if ((entity.m_tag == EntityTag::PlayerSnake || entity.m_tag == EntityTag::AISnake) 
			&& GameLogicLocator::get().isSnakeAllowedToMove())
		{
			handleSnakeMovement(entity, entityManager);
		}
	}
}

void SystemMovable::handleSnakeMovement(Entity & entity, EntityManager & entityManager) const
{
	const Direction moveDirection = entityManager.getEntityComponent<ComponentMovable>(entity, ComponentType::Movable).m_movementDirection;
	auto& componentPosition = entityManager.getEntityComponent<ComponentPosition>(entity, ComponentType::Position);
	componentPosition.m_oldPosition = componentPosition.m_position;
	switch (moveDirection)
	{
	case Direction::Left:
	{
		componentPosition.m_position.x -= 25.0f;
		break;
	}
	case Direction::Right:
	{
		componentPosition.m_position.x += 25.0f;
		break;
	}
	case Direction::Up:
	{
		componentPosition.m_position.y -= 25.0f;
		break;
	}
	case Direction::Down:
	{
		componentPosition.m_position.y += 25.0f;
		break;
	}
	case Direction::None :
	{
		std::cout << "DIRECTION NONE\n";
		break;
	}
	}
}

void SystemMovable::onSystemMessage(const SystemMessage & systemMessage) const
{
	auto& entityManager = EntityManagerLocator::get();
	auto& componentMovable = entityManager.getEntityComponent<ComponentMovable>(*systemMessage.m_entity, ComponentType::Movable);
	switch (systemMessage.m_systemEvent)
	{
	case SystemEvent::MoveLeft :
	{
		componentMovable.m_movementDirection = Direction::Left;
		break;
	}
	case SystemEvent::MoveRight :
	{
		componentMovable.m_movementDirection = Direction::Right;
		break;
	}
	case SystemEvent::MoveUp :
	{
		componentMovable.m_movementDirection = Direction::Up;
		break;
	}
	case SystemEvent::MoveDown :
	{
		componentMovable.m_movementDirection = Direction::Down;
		break;
	}
	}
}