#pragma once
#include "Group.h"

class GroupManager
{
public:
	static GroupManager* instance();
public:
	~GroupManager();
	void render();
	void update();

	void addGroup(Group * group);
private:
	GroupManager();

	std::vector<Group*> m_Groups;
};

