#include "Game.h"

Game::Game()
	: m_window(sf::Vector2i(480, 640), "Snake")
{
}

bool Game::isRunning() const
{
	return m_window.isOpen();
}

void Game::update()
{
	m_window.update();
}

void Game::draw()
{
	m_window.clearScreen();
	m_window.display();
}

void Game::lateUpdate()
{
}
