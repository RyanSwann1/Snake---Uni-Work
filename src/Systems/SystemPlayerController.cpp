#include <Systems\SystemPlayerController.h>
#include <Managers\EntityManager.h>
#include <Locators\EntityManagerLocator.h>
#include <Managers\SystemManager.h>

SystemPlayerController::SystemPlayerController(SystemManager& systemManager, SystemType type)
	: SystemBase(systemManager, type)
{}

void SystemPlayerController::update() const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (entity.m_tag != EntityTag::PlayerSnake)
		{
			continue;
		}

		handlePlayerInput(entity);
	}
}

void SystemPlayerController::handlePlayerInput(Entity& entity) const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_systemManager.addSystemMessage(SystemMessage(SystemType::Movable, SystemEvent::MoveLeft, &entity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_systemManager.addSystemMessage(SystemMessage(SystemType::Movable, SystemEvent::MoveRight, &entity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_systemManager.addSystemMessage(SystemMessage(SystemType::Movable, SystemEvent::MoveDown, &entity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_systemManager.addSystemMessage(SystemMessage(SystemType::Movable, SystemEvent::MoveUp, &entity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		m_systemManager.addSystemMessage(SystemMessage(SystemType::Snake, SystemEvent::ExtendSnake, &entity));
	}
}
