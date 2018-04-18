#pragma once

#include <Entity\EntityTag.h>
#include <Components\ComponentBase.h>
#include <SFML\Graphics.hpp>
#include <array>
#include <memory>

class Entity
{
public:
	Entity(int ID, EntityTag tag)
		: m_ID(ID),
		m_tag(tag)
	{}

	const int m_ID;
	const EntityTag m_tag;
	std::array<std::unique_ptr<ComponentBase>, static_cast<size_t>(ComponentType::Total)> m_components;
};