#include "FontManager.h"
#include "freetype-gl/freetype-gl.h"

Font* FontManager::defaultFont()
{
	Font* font = new Font("Consolas", "./res/font/Consolas.ttf", 20);
	add(font);
	return font;
}

std::vector<Font*> FontManager::m_Fonts;

void FontManager::add(Font* font)
{
	for (auto &f : m_Fonts)
	{
		if (f->getName() == font->getName())
			return;
	}

	m_Fonts.push_back(font);
}

Font* FontManager::get()
{
	if (m_Fonts.size() > 0)
		return m_Fonts.at(0);
	else
		return FontManager::defaultFont();
}

Font* FontManager::get(const std::string& name)
{
	for (auto &f : m_Fonts)
	{
		if (f->getName() == name)
			return f;
	}
	return FontManager::defaultFont();;
}

Font* FontManager::get(const std::string& name, unsigned int size)
{
	for (auto &f : m_Fonts)
	{
		if (f->getName() == name && f->getSize() == size)
			return f;
	}
	return nullptr;
}

void FontManager::clean()
{
	for (auto &f : m_Fonts)
		delete &f;
}
