#pragma once

#include <assert.h>

class TextureManager;
class TextureManagerLocator
{
public:
	TextureManagerLocator() = delete;

	static void provide(TextureManager& textureManager)
	{
		m_textureManager = &textureManager;
	}

	static TextureManager& get()
	{
		assert(m_textureManager);
		return *m_textureManager;
	}

private:
	
	static TextureManager* m_textureManager;
};