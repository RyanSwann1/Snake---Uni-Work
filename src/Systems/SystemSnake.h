#pragma once

#include <Systems\SystemBase.h>
#include <Game\Direction.h>
#include <SFML\Graphics.hpp>

class ComponentPosition;
class EntityManager;
class Entity;
class SystemSnake : public SystemBase
{
public:
	SystemSnake(SystemManager& systemManager, SystemType systemType);
	SystemSnake(const SystemSnake&) = delete;
	SystemSnake& operator=(const SystemSnake&) = delete;
	SystemSnake(SystemSnake&&) = delete;
	SystemSnake& operator=(SystemSnake&&) = delete;

	void update() const override final;
	void onSystemMessage(const SystemMessage& systemMessage) const override final;

private:
	void handleSnakeMovement(Entity& entity, EntityManager& entityManager) const;
	void extendSnake(Entity& entity) const;
};