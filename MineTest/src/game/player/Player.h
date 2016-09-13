#pragma once
#include "../../Defines.h"
#include "../../render/api/Camera.h"
#include "glm/glm.hpp"
#include <mutex>

class Player
{
private:
public:
	Camera m_Camera;
	glm::vec3 getPosition();
	void update();
private:
	void movement();

private:
	std::mutex m_PositionLock;
	glm::vec3 m_Position;
};