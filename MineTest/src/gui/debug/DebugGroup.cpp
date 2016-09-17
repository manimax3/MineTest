#include "DebugGroup.h"
#include "../../game/player/Player.h"
#include "../GroupManager.h"
#include "../../util/Input.h"
#include "../../game/registry/GameRegistry.h"

DebugGroup::DebugGroup(uint &fps, uint &ups)
	: player(GameRegistry::instance().getPlayer()), ups(ups), fps(fps)
{
	m_Visible = false;
	updLab = new Label("FPS: %% UPS: %%");
	posLab = new Label("Player: %% %% %% Chunk: %% %%", glm::vec2(0, SCREEN_HEIGHT - 50));
	addRenderable(updLab);
	addRenderable(posLab);

	GroupManager::instance()->addGroup(this);
}

DebugGroup::~DebugGroup()
{
}

void DebugGroup::render()
{
	if (m_Visible)
		Group::render();
}

void DebugGroup::update()
{
	if (!m_Visible)
		return;

	std::string text = "FPS: " + std::to_string(fps) + " UPS: " + std::to_string(ups);
	updLab->setText(text);
	text = "Player: " + std::to_string((int)std::floorf(player.getPosition().x)) + " " +
						std::to_string((int)std::floorf(player.getPosition().y)) + " " +
						std::to_string((int)std::floorf(player.getPosition().z)) + " Chunk: " +
						std::to_string((int)std::floorf(player.getPosition().x / 16)) + " " +
						std::to_string((int)std::floorf(player.getPosition().z / 16));
	posLab->setText(text);
}
