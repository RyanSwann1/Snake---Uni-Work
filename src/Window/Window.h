#pragma once

#include <string>
#include <SFML\Graphics.hpp>

class Window
{
public:
	Window(const sf::Vector2i& size, std::string&& name);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window&& operator=(Window&&) = delete;

	bool isOpen() const;
	void clearScreen();
	void update();
	void display();
	void draw(const sf::Sprite& sprite);

private:
	sf::RenderWindow m_window;
	bool m_fullScreen;

	void closeWindow();
};