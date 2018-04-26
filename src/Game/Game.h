#pragma once

#include <Window\Window.h>
#include <Managers\EntityManager.h>
#include <Managers\SystemManager.h>
#include <Managers\TextureManager.h>
#include <Game\GameClock.h>
#include <Game\GameLogic.h>

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game&& operator=(Game&&) = delete;

	bool isRunning() const;
	void update();
	void draw();
	void lateUpdate();

private:
	SystemManager m_systemManager;
	TextureManager m_textureManager;
	EntityManager m_entityManager;
	Window m_window;
	GameClock m_gameClock;
	GameLogic m_gameLogic;
};