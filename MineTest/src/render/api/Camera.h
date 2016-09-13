#pragma once
#include "../../Defines.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);
	const glm::vec3 WORLD_RIGHT = glm::vec3(1, 0, 0);
	const float MOUSE_SENSITIVY = 0.3;
	const glm::mat4 PROJECTION_MAT = glm::perspective(45.f, (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.f);


	void calculateRotation(float xOffset, float yOffset);

	glm::mat4 getViewMatrix();
	glm::mat4 getVPMatrix();
	glm::vec3 m_Direction;
	Camera();
private:
	glm::vec3 m_Right, m_Up;
	glm::vec3 m_Position;
	float m_Pitch = 0, m_Yaw = -90.f;
private:
	void updateCameraVectors();

	friend class Player;
};