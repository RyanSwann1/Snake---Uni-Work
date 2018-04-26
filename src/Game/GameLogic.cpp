#include <Game\GameLogic.h>
#include <Locators\GameClockLocator.h>
#include <Game\GameClock.h>
#include <Locators\GameLogicLocator.h>
#include <iostream>

//Game Logic
GameLogic::GameLogic()
	: m_gameTimer(0),
	m_snakeMovementTimer(0),
	m_timeUntilSnakeMovementAllowed(.75f),
	m_totalGameTime(90.0f)
{
	GameLogicLocator::provide(*this);
}

void GameLogic::update()
{
	const auto& gameClock = GameClockLocator::get();
	m_gameTimer += gameClock.getFrameTime();
	m_snakeMovementTimer += gameClock.getFrameTime();
}

bool GameLogic::isSnakeAllowedToMove()
{
	if (m_snakeMovementTimer >= m_timeUntilSnakeMovementAllowed)
	{
		resetTimeUntilSnakeMovementAllowed();
		std::cout << "Move\n";
		return true;
	}

	return false;
}

void GameLogic::resetTimeUntilSnakeMovementAllowed()
{
	m_snakeMovementTimer = 0.0f;
}