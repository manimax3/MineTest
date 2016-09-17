#pragma once
#include "Renderable2D.h"

class Group : public Renderable2D
{
public:
	Group(glm::vec2 position = glm::vec2(0, 0));
	~Group();

	virtual void render() override;
	virtual void update() override;

	/*
		Adds renderable 
		Once added the renderable gets deleted on destruction of group
		every renderable position gets translated by the groups position
	*/
	void addRenderable(Renderable2D *renderable);

private:
	std::vector<Renderable2D*> m_Renderables;
};

