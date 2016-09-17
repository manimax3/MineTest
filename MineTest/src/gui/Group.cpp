#include "Group.h"

Group::Group(glm::vec2 position)
{
	setPosition(position);
}

Group::~Group()
{
	for (auto &renderable : m_Renderables)
		delete renderable;
}

void Group::render()
{
	for (auto &renderable : m_Renderables)
		renderable->render();
}

void Group::update()
{
	for (auto &renderable : m_Renderables)
		renderable->update();
}

void Group::addRenderable(Renderable2D *renderable)
{
	renderable->setPosition(renderable->getPosition() + this->getPosition());
	m_Renderables.push_back(renderable);
}
