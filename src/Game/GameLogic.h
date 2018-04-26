#pragma once

#include <SFML\Graphics.hpp>

class GameLogic
{
public:
	GameLogic();
	GameLogic(const GameLogic&) = delete;
	GameLogic& operator=(const GameLogic&) = delete;
	GameLogic(GameLogic&&) = delete;
	GameLogic&& operator=(GameLogic&&) = delete;

	void update();
	bool isSnakeAllowedToMove();

private:
	float m_gameTimer;
	float m_snakeMovementTimer;
	const float m_timeUntilSnakeMovementAllowed;
	const float m_totalGameTime;

	void resetTimeUntilSnakeMovementAllowed();
};