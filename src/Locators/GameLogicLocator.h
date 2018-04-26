#pragma once

#include <assert.h>

class GameLogic;
class GameLogicLocator
{
public:
	GameLogicLocator() = delete;

	static void provide(GameLogic& gameLogic)
	{
		m_gameLogic = &gameLogic;
	}

	static GameLogic& get()
	{
		assert(m_gameLogic);
		return *m_gameLogic;
	}

private:
	static GameLogic* m_gameLogic;
};