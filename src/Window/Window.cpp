#include "Window.h"
#include <utility>

Window::Window(const sf::Vector2i& size, std::string&& name)
	: m_window(sf::VideoMode(size.x, size.y), std::move(name), sf::Style::Default),
	m_fullScreen(false)
{}

bool Window::isOpen() const
{
	return m_window.isOpen();
}

void Window::clearScreen()
{
	m_window.clear(sf::Color::Black);
}

void Window::update()
{
	sf::Event sfmlEvent;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(sfmlEvent))
		{
			if (sfmlEvent.type == sf::Event::Closed)
			{
				closeWindow();
			}
		}
	}
}

void Window::display()
{
	m_window.display();
}

void Window::draw(const sf::Sprite & sprite)
{
	m_window.draw(sprite);
}

void Window::closeWindow()
{
	m_window.close();
}