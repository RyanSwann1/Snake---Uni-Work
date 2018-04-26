#include <Systems\SystemDrawable.h>
#include <Locators\EntityManagerLocator.h>
#include <managers\EntityManager.h>
#include <Components\ComponentDrawable.h>
#include <Components\ComponentPosition.h>

SystemDrawable::SystemDrawable(SystemManager& systemManager, SystemType type)
	: SystemBase(systemManager, type)
{}

void SystemDrawable::render(sf::RenderWindow & window) const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (!SystemBase::entityHasComponent(entity, ComponentType::Drawable))
		{
			continue;
		}
		
		drawSprite(entityManager, window, entity);
	}
}

void SystemDrawable::drawSprite(EntityManager& entityManager, sf::RenderWindow& window, const Entity & entity) const
{
	auto& drawableComponent = entityManager.getEntityComponent<ComponentDrawable>(entity, ComponentType::Drawable);
	const auto& positionComponent = entityManager.getEntityComponent<ComponentPosition>(entity, ComponentType::Position);
	drawableComponent.m_sprite.setPosition(positionComponent.m_position);
	window.draw(drawableComponent.m_sprite);
}