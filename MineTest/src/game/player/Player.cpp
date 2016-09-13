#include "Player.h"
#include "../../util/Input.h"
#include "GLFW/glfw3.h"

glm::vec3 Player::getPosition()
{
	std::lock_guard<std::mutex> lock(m_PositionLock);
	return m_Position;
}

void Player::update()
{
	movement();
}

void Player::movement()
{
	std::lock_guard<std::mutex> lock(m_PositionLock);

	if (Input::instance().isKeyPressed(GLFW_KEY_W))
		m_Position += m_Camera.m_Direction * 0.25f;
	if (Input::instance().isKeyPressed(GLFW_KEY_S))
		m_Position -= m_Camera.m_Direction * 0.25f;
	if (Input::instance().isKeyPressed(GLFW_KEY_A))
		m_Position -= m_Camera.m_Right * 0.25f;
	if (Input::instance().isKeyPressed(GLFW_KEY_D))
		m_Position += m_Camera.m_Right * 0.25f;
	m_Camera.m_Position = m_Position;
}
