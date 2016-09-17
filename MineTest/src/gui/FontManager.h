#pragma once
#include "../Defines.h"
#include "Font.h"

class FontManager
{
public:
	static void add(Font* font);
	static Font* get();
	static Font* get(const std::string& name);
	static Font* get(const std::string& name, unsigned int size);
	static void clean();
private:
	FontManager() { }

	static std::vector<Font*> m_Fonts;
};