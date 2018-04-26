#include <Managers\SystemManager.h>
#include <Systems\SystemDrawable.h>
#include <Systems\SystemSnake.h>
#include <Systems\SystemPlayerController.h>
#include <Systems\SystemMovable.h>

//System Manager
SystemManager::SystemFactory::SystemFactory(SystemManager& systemManager)
{
	registerSystem<SystemDrawable>(systemManager, SystemType::Drawable);
	registerSystem<SystemSnake>(systemManager, SystemType::Snake);
	registerSystem<SystemPlayerController>(systemManager, SystemType::PlayerController);
	registerSystem<SystemMovable>(systemManager, SystemType::Movable);
}

std::unique_ptr<SystemBase> SystemManager::SystemFactory::getSystem(SystemType type) const
{
	auto iter = m_systemFactory.find(type);
	assert(iter != m_systemFactory.cend());
	return iter->second();
}

//System Manager
SystemManager::SystemManager()
	: m_systemFactory(*this),
	m_systems(getSystems()),
	m_systemMessages()
{
	assert(!m_systems.empty());
}

void SystemManager::addSystemMessage(const SystemMessage & systemMessage)
{
	m_systemMessages.push_back(systemMessage);
}

void SystemManager::update()
{
	for (const auto& system : m_systems)
	{
		system->update();
	}

	handleSystemMessages();
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
	systems[static_cast<int>(SystemType::Snake)] = m_systemFactory.getSystem(SystemType::Snake);
	systems[static_cast<int>(SystemType::PlayerController)] = m_systemFactory.getSystem(SystemType::PlayerController);
	systems[static_cast<int>(SystemType::Movable)] = m_systemFactory.getSystem(SystemType::Movable);

	return systems;
}

void SystemManager::handleSystemMessages()
{
	for (const auto& systemMessage : m_systemMessages)
	{
		sendSystemMessage(systemMessage);
	}

	m_systemMessages.clear();
}

void SystemManager::sendSystemMessage(const SystemMessage & systemMessage) const
{
	m_systems[static_cast<int>(systemMessage.m_systemType)].get()->onSystemMessage(systemMessage);
}