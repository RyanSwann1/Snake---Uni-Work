#pragma once

#include "ComponentBase.h"
#include <vector>
#include <SFML\Graphics.hpp>

class ComponentPosition;
class ComponentSnake : public ComponentBase
{
public:
	ComponentSnake(ComponentType type)
		: ComponentBase(type)
	{}

	std::vector<std::unique_ptr<ComponentPosition>> m_snake;
};