#include "Game.h"
#include <Locators\EntityManagerLocator.h>
#include <iostream>

Game::Game()
	: m_entityManager(),
	m_window(sf::Vector2i(480, 640), "Snake")
{
	m_entityManager.addEntity(sf::Vector2f(64, 64), EntityName::Snake, EntityTag::Snake);
}

bool Game::isRunning() const
{
	return m_window.isOpen();
}

void Game::update()
{
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

}