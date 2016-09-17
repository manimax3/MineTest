#pragma once
#include "../Defines.h"

class Renderable2D
{
public:
	Renderable2D() = default;
	virtual ~Renderable2D() = default;



	 virtual void render() = 0;
	 virtual void update() = 0;

	 glm::vec2 getPosition() const { return m_Position; }
	 void setPosition(glm::vec2 val) { m_Position = val; }

	 glm::vec2 getUV() const { return m_UV; }
	 void setUV(glm::vec2 val) { m_UV = val; }

	 glm::vec2 getSize() const { return m_Size; }
	 void setSize(glm::vec2 val) { m_Size = val; }

	 glm::vec3 getColor() const { return m_Color; }
void setColor(glm::vec3 val) { m_Color = val; }
protected:
	glm::vec2 m_Position;
	glm::vec2 m_UV;
	glm::vec2 m_Size;
	glm::vec3 m_Color;
};