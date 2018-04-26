#include <Systems\SystemBase.h>
#include <Entity\Entity.h>
#include <Components\ComponentType.h>
#include <assert.h>

SystemBase::SystemBase(SystemManager& systemManager, SystemType type)
	: m_systemManager(systemManager),
	m_systemType(type)
{}

bool SystemBase::entityHasComponent(Entity & entity, ComponentType componentType) const
{
	if (!entity.m_components[static_cast<int>(componentType)])
	{
		return false;
	}

	return entity.m_components[static_cast<int>(componentType)]->m_componentType == componentType;
}