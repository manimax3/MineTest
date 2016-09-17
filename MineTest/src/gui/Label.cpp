#include "Label.h"
#include "FontManager.h"
#include "..\render\Renderer2D.h"

Label::Label(std::string text, glm::vec2 position, std::string fontname, glm::vec3 color)
	: m_Text(text), m_FontName(fontname)
{
	setPosition(position);
	setColor(color);
}

Label::~Label()
{
}

void Label::render()
{
	Renderer2D::instance()->submitText(m_Text, m_Position, *FontManager::get(m_FontName), m_Color);
}

void Label::update()
{}
