#pragma once

#include <assert.h>

class GameClock;
class GameClockLocator
{
public:
	GameClockLocator() = delete;

	static void provide(GameClock& gameClock)
	{
		m_gameClock = &gameClock;
	}

	static GameClock& get()
	{
		assert(m_gameClock);
		return *m_gameClock;
	}

private:
	static GameClock* m_gameClock;
};