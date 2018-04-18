#include <Managers\SystemManager.h>
#include <Systems\SystemDrawable.h>
#include <Systems\SystemSnake.h>

//System Manager
SystemManager::SystemFactory::SystemFactory()
{
	registerSystem<SystemDrawable>(SystemType::Drawable);
	registerSystem<SystemSnake>(SystemType::Snake);
}

std::unique_ptr<SystemBase> SystemManager::SystemFactory::getSystem(SystemType type) const
{
	auto iter = m_systemFactory.find(type);
	assert(iter != m_systemFactory.cend());
	return iter->second();
}

//System Manager
SystemManager::SystemManager()
	: m_systemFactory(),
	m_systems(getSystems())
{
	assert(!m_systems.empty());
}

void SystemManager::update() const
{
	for (auto& system : m_systems)
	{
		system->update();
	}
}

void SystemManager::render(sf::RenderWindow& window) const
{
	assert(m_systems[static_cast<int>(SystemType::Drawable)].get());
	static_cast<SystemDrawable*>(m_systems[static_cast<int>(SystemType::Drawable)].get())->render(window);
}

std::array<std::unique_ptr<SystemBase>, static_cast<size_t>(SystemType::Total)> SystemManager::getSystems() const
{
	std::array<std::unique_ptr<SystemBase>, static_cast<size_t>(SystemType::Total)> systems;
	systems[static_cast<int>(SystemType::Drawable)] = m_systemFactory.getSystem(SystemType::Drawable);

	return systems;
}