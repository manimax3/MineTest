#include "Texture2D.h"
#include "SOIL/SOIL.h"


Texture2D::Texture2D()
{
	GLCall(glGenTextures(1, &m_TextureID));
}

Texture2D::Texture2D(uint &custom_id)
	: m_TextureID(custom_id)
{
	GLCall(glGenTextures(1, &m_TextureID));
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture2D::loadFromFile(std::string path, TextureProperties &properties)
{
	m_Properties = properties;
	byte *pixels = SOIL_load_image(path.c_str(), &m_Properties.width, &m_Properties.height, 0, SOIL_LOAD_RGB);

	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Properties.width, m_Properties.height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Properties.FilterMin));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Properties.FilterMag));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Properties.Wrapping_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Properties.Wrapping_T));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	SOIL_free_image_data(pixels);
}

void Texture2D::loadFromMemory(byte* data, TextureProperties &properties)
{
	m_Properties = properties;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Properties.width, m_Properties.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Properties.FilterMin));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Properties.FilterMag));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Properties.Wrapping_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Properties.Wrapping_T));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::bind(uint unit)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + unit));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}
