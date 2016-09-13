#pragma once
#include"../../Defines.h"
#include "TextureProperties.h"
#include <vector>
class Texture2DArray
{
public:
	Texture2DArray();
	~Texture2DArray();

	void loadFromFiles(const std::vector<std::string> &files, const TextureProperties &properties);
	void bind();
private:
	uint m_TextureID;
	TextureProperties m_Properties;
};