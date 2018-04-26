#pragma once

#include <Components\ComponentBase.h>
#include <Game\Direction.h>

class ComponentMovable : public ComponentBase
{
public:
	ComponentMovable(ComponentType type)
		: ComponentBase(type),
		m_movementDirection(Direction::None)
	{}

	Direction m_movementDirection;
};