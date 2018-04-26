#pragma once

#include "ComponentPosition.h"
#include <vector>
#include <memory>

class ComponentSnake : public ComponentBase
{
public:
	ComponentSnake(ComponentType type)
		: ComponentBase(type),
		m_snake()
	{}

	std::vector<std::pair<std::unique_ptr<ComponentPosition>, std::unique_ptr<ComponentDrawable>>> m_snake;
};