#pragma once
#include "../../Defines.h"
#include "TextureProperties.h"
#include <string>

class Texture2D
{
public:
	Texture2D();
	Texture2D(uint &custom_id);
	~Texture2D();

	void loadFromFile(std::string path, TextureProperties &properties);
	void loadFromMemory(byte* data, TextureProperties &properties);
	void bind(uint unit = 0);
	inline uint getID() { return m_TextureID; }

private:
	uint m_TextureID;
	TextureProperties m_Properties;
};


