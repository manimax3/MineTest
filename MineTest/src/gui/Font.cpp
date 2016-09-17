#include "Font.h"
#include "freetype-gl/freetype-gl.h"

Font::Font(const std::string& name, const std::string& filename, float size)
	: m_Name(name), m_Filename(filename), m_Size(size), m_Scale(glm::vec2(1.0f, 1.0f))
{
	m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
	m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
	assert(m_FTFont);

	GLCall(texture_atlas_upload(m_FTAtlas));
}

Font::~Font()
{
	GLCall(glDeleteTextures(1, &m_FTAtlas->id));
	texture_atlas_clear(m_FTAtlas);
}

void Font::setScale(float x, float y)
{
	m_Scale = glm::vec2(x, y);
}

uint Font::getID() const
{
	return m_FTAtlas->id;
}
