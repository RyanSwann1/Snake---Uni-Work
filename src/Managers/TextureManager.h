#pragma once

#include <Managers\ResourceManager.h>
#include <Locators\TextureManagerLocator.h>
#include <SFML\Graphics.hpp>

class TextureManager : public ResourceManager<sf::Texture>
{
public:
	TextureManager()
	{
		TextureManagerLocator::provide(*this);
	}
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager&& operator=(TextureManager&&) = delete;


private:
	sf::Texture loadResourceFromFile(const std::string& fileName) const override final
	{
		sf::Texture texture;
		const bool textureLoaded = texture.loadFromFile(fileName);
		assert(textureLoaded);
		return texture;
	}
};