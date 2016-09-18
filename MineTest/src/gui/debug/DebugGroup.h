#pragma once
#include "..\Group.h"
#include "..\Label.h"
#include "..\..\util\IKeyListener.h"

class Player;

class DebugGroup : public Group, public IKeyListener
{
public:
	DebugGroup(uint &fps, uint &ups);
	~DebugGroup();


	virtual void render() override;
	virtual void update() override;

	bool isVisible() const { return m_Visible; }
	void Visible(bool val) { m_Visible = val; }
private:
	bool m_Visible;
	uint &fps, &ups;
	Player &player;

	Label *updLab, *posLab;

	virtual void onKeyPressed(int key) override;
	virtual void onKeyReleased(int key) override;

};

