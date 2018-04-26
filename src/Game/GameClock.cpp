#include <Game\GameClock.h>
#include <Locators\GameClockLocator.h>
#include <iostream>

GameClock::GameClock()
	: m_gameClock(),
	m_frameTime(0.0f)
{
	GameClockLocator::provide(*this);
}

void GameClock::update()
{
	m_frameTime = m_gameClock.restart().asSeconds();
}

float GameClock::getFrameTime() const
{
	return m_frameTime;;
}