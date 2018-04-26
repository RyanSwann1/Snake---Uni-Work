#pragma once

#include <Systems\SystemType.h>

class SystemMessage;
class SystemManager;
class Entity;
enum class ComponentType;
class SystemBase
{
public:
	SystemBase(SystemManager& systemManager, SystemType type);
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;
	
	virtual void update() const {}
	virtual void onSystemMessage(const SystemMessage& systemMessage) const {}
	
protected:
	SystemManager& m_systemManager;
	bool entityHasComponent(Entity& entity, ComponentType componentType) const;

private:
	const SystemType m_systemType;
};