#pragma once

#include <array>
#include <Systems\SystemBase.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include <assert.h>
#include <SFML\Graphics.hpp>
#include <Systems\SystemMessage.h>
#include <vector>

class SystemManager
{
	class SystemFactory
	{
	public:
		SystemFactory(SystemManager& systemManager);
		SystemFactory(const SystemFactory&) = delete;
		SystemFactory& operator=(const SystemFactory&) = delete;
		SystemFactory(SystemFactory&&) = delete;
		SystemFactory&& operator=(SystemFactory&&) = delete;
		
		std::unique_ptr<SystemBase> getSystem(SystemType type) const;

	private:
		std::unordered_map<SystemType, std::function<std::unique_ptr<SystemBase>()>> m_systemFactory;

		template <class System>
		void registerSystem(SystemManager& systemManager, SystemType type)
		{
			assert(m_systemFactory.find(type) == m_systemFactory.cend());
			m_systemFactory.emplace(type, [&systemManager, type]() -> std::unique_ptr<System>
			{ 
				return std::make_unique<System>(systemManager, type);
			});
		}
	};

public:
	SystemManager();
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager&& operator=(SystemManager&&) = delete;

	void addSystemMessage(const SystemMessage& systemMessage);
	void update();
	void render(sf::RenderWindow& window) const;
	
private:
	const SystemFactory m_systemFactory;
	const std::array<std::unique_ptr<SystemBase>, static_cast<size_t>(SystemType::Total)> m_systems;
	std::vector<SystemMessage> m_systemMessages;

	std::array<std::unique_ptr<SystemBase>, static_cast<size_t>(SystemType::Total)> getSystems() const;
	void handleSystemMessages();
	void sendSystemMessage(const SystemMessage& systemMessage) const;
};