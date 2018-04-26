#pragma once

#include <Systems\SystemBase.h>

class Entity;
class SystemPlayerController : public SystemBase
{
public:
	SystemPlayerController(SystemManager& systemManager, SystemType type);
	SystemPlayerController(const SystemPlayerController&) = delete;
	SystemPlayerController& operator=(const SystemPlayerController&) = delete;
	SystemPlayerController(SystemPlayerController&&) = delete;
	SystemPlayerController&& operator=(SystemPlayerController&&) = delete;

	void update() const override final;

private:
	void handlePlayerInput(Entity& entity) const;
};