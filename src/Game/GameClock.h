#pragma once

#include <SFML\Graphics.hpp>

class GameClock
{
public:
	GameClock();
	GameClock(const GameClock&) = delete;
	GameClock& operator=(const GameClock&) = delete;
	GameClock(GameClock&&) = delete;
	GameClock&& operator=(GameClock&&) = delete;

	void update();
	float getFrameTime() const;

private:
	sf::Clock m_gameClock;
	float m_frameTime;
};