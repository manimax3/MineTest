#pragma once
#include "../Defines.h"

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

class Font
{
public:
	Font(const std::string& name, const std::string& filename, float size);
	~Font();

	void setScale(float x, float y);
	uint getID() const;

	inline ftgl::texture_font_t* getFTFont() { return m_FTFont; }
	inline const glm::vec2& getScale() const { return m_Scale; }
	inline const std::string& getName() const { return m_Name; }
	inline const std::string& getFileName() const { return m_Filename; }
	inline const float getSize() const { return m_Size; }

private:
	ftgl::texture_atlas_t* m_FTAtlas;
	ftgl::texture_font_t* m_FTFont;
	float m_Size;
	glm::vec2 m_Scale;
	std::string m_Name;
	std::string m_Filename;
};
