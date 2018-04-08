#pragma once

#include "ComponentBase.h"
#include <vector>
#include <SFML\Graphics.hpp>

class ComponentSnake : public ComponentBase
{
public:
	ComponentSnake(ComponentType type)
		: ComponentBase(type),
		m_snake()
	{}

	std::vector<sf::RectangleShape> m_snake;
};