#pragma once

#include <Systems\SystemBase.h>

class EntityManager;
class Entity;
class SystemMovable : public SystemBase
{
public:
	SystemMovable(SystemManager& systemManager, SystemType systemType);
	SystemMovable(const SystemMovable&) = delete;
	SystemMovable& operator=(const SystemMovable&) = delete;
	SystemMovable(SystemMovable&&) = delete;
	SystemMovable&& operator=(SystemMovable&&) = delete;

	void update() const override final;
	void onSystemMessage(const SystemMessage& systemMessage) const override final;

private:
	void handleSnakeMovement(Entity& entity, EntityManager& entityManager) const;
};