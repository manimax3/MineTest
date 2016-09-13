#include "Camera.h"

void Camera::calculateRotation(float xOffset, float yOffset)
{
	xOffset *= this->MOUSE_SENSITIVY;
	yOffset *= this->MOUSE_SENSITIVY;

	this->m_Yaw += xOffset;
	this->m_Pitch += yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped

   if (this->m_Pitch > 89.0f)
		this->m_Pitch = 89.0f;
	if (this->m_Pitch < -89.0f)
		this->m_Pitch = -89.0f;

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->m_Position, this->m_Position + this->m_Direction, this->m_Up);
}

glm::mat4 Camera::getVPMatrix()
{
	glm::mat4 proj = PROJECTION_MAT;
	return proj * getViewMatrix();
}

Camera::Camera()
	: m_Up(WORLD_UP), m_Right(WORLD_RIGHT)
{
	this->updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
	front.y = sin(glm::radians(this->m_Pitch));
	front.z = sin(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
	this->m_Direction = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->m_Right = glm::normalize(glm::cross(this->m_Direction, this->m_Up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//this->m_Up = glm::normalize(glm::cross(this->m_Right, this->m_Direction));
}
