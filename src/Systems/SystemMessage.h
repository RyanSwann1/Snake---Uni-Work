#pragma once

#include <Systems\SystemEvent.h>
#include <Systems\SystemType.h>

class Entity;
class SystemMessage
{
public:
	SystemMessage(SystemType systemType, SystemEvent systemEvent, Entity* entity = nullptr)
		: m_systemType(systemType),
		m_systemEvent(systemEvent),
		m_entity(entity)
	{}

	const SystemType m_systemType;
	const SystemEvent m_systemEvent;
	Entity* m_entity;
};