#pragma once
#include "../Defines.h"
#include "Renderable2D.h"

class Label : public Renderable2D
{
public:
	Label(std::string text = "Default Text", glm::vec2 position = glm::vec2(0,0), std::string fontname = "Consolas", glm::vec3 color = glm::vec3(0,0,0));
	~Label();


	virtual void render() override;
	virtual void update() override;

	void setFont(std::string val) { m_FontName = val; }
	std::string getText() const { return m_Text; }
	void setText(std::string val) { m_Text = val; }
private:
	std::string m_FontName;
	std::string m_Text;
};