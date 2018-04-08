#pragma once

#include <Components\ComponentBase.h>
#include <SFML\Graphics.hpp>

class ComponentPosition : public ComponentBase
{
public:
	ComponentPosition(ComponentType type)
		: ComponentBase(type),
		m_position()
	{}

	sf::Vector2f m_position;
	sf::Vector2f m_oldPosition;
};