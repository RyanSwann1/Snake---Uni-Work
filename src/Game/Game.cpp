#include "Game.h"

Game::Game()
	: m_systemManager(),
	m_textureManager(),
	m_entityManager(),
	m_window(sf::Vector2i(480, 640), "Snake"),
	m_gameClock(),
	m_gameLogic()
{
	m_textureManager.addResource("CollidableTile.PNG");
	m_entityManager.addEntity(sf::Vector2f(64, 64), EntityName::Snake, EntityTag::PlayerSnake);
}

bool Game::isRunning() const
{
	return m_window.isOpen();
}

void Game::update()
{
	m_gameLogic.update();
	m_systemManager.update();
	m_entityManager.update();
	m_window.update();
}

void Game::draw()
{
	m_window.clearScreen();
	m_systemManager.render(m_window.getWindow());
	m_window.display();
}

void Game::lateUpdate()
{
	m_gameClock.update();
}