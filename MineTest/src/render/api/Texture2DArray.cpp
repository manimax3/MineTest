#include "Texture2DArray.h"
#include "SOIL/SOIL.h"

Texture2DArray::Texture2DArray()
{
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_TextureID);
}

Texture2DArray::~Texture2DArray()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture2DArray::loadFromFiles(const std::vector<std::string> &files, const TextureProperties &properties)
{
	m_Properties = properties;
	
	GLCall(;);
	GLCall(glTextureStorage3D(m_TextureID, 6, GL_RGB8, m_Properties.width, m_Properties.height, files.size()));

	GLCall(glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_Properties.FilterMin));
	GLCall(glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, m_Properties.FilterMag));
	GLCall(glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, m_Properties.Wrapping_S));
	GLCall(glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, m_Properties.Wrapping_T));

	uint i = 0;
	for (auto &file : files)
	{
		int w, h;
		byte* pixels = SOIL_load_image(file.c_str(), &w, &h, 0, SOIL_LOAD_RGB);
		GLCall(glTextureSubImage3D(m_TextureID, 0, 0, 0, i, m_Properties.width, m_Properties.height, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels));
		SOIL_free_image_data(pixels);
		i++;
	}

	GLCall(glGenerateTextureMipmap(m_TextureID));
}

void Texture2DArray::bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID));
}
