#pragma once

#include <Systems\SystemBase.h>
#include <SFML\Graphics.hpp>

class EntityManager;
class SystemDrawable : public SystemBase
{
public:
	SystemDrawable(SystemManager& systemManager, SystemType type);
	SystemDrawable(const SystemDrawable&) = delete;
	SystemDrawable& operator=(const SystemDrawable&) = delete;
	SystemDrawable(SystemDrawable&&) = delete;
	SystemDrawable&& operator=(SystemDrawable&&) = delete;

	void render(sf::RenderWindow& window) const;
	
private:
	void drawSprite(EntityManager& entityManager, sf::RenderWindow& window, const Entity& entity) const;
};