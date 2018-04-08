#pragma once

#include <Components\ComponentType.h>

class ComponentBase
{
public:
	ComponentBase(ComponentType type)
		: m_componentType(type)
	{}

	const ComponentType m_componentType;
};