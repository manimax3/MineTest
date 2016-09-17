#include "GroupManager.h"

GroupManager* GroupManager::instance()
{
	static GroupManager* instance = new GroupManager;
	return instance;
}

GroupManager::GroupManager()
{
}

GroupManager::~GroupManager()
{
	for (auto &g : m_Groups)
		delete g;
}

void GroupManager::render()
{
	for (auto &g : m_Groups)
		g->render();
}

void GroupManager::update()
{
	for (auto &g : m_Groups)
		g->update();
}

void GroupManager::addGroup(Group * group)
{
	m_Groups.push_back(group);
}
