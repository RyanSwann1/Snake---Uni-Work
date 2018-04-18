#pragma once

#include <Components\ComponentBase.h>

class ComponentDrawable : public ComponentBase
{
public:
	ComponentDrawable(ComponentType type)
		: ComponentBase(type),
		m_sprite()
	{

	}

	sf::Sprite m_sprite;
};