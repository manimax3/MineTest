#pragma once

class GLFWwindow;

class Input
{
public:
	static Input& instance();
	inline void getMousePos(float *x, float *y) { *x = m_MouseX; *y = m_MouseY; }
	inline bool isKeyPressed(int key) { return keys[key]; }
private:
	Input();
	float m_MouseX = 0, m_MouseY = 0;
	bool keys[1024];
public:
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};