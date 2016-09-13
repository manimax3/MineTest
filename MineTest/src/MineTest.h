#pragma once

#include "Defines.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class MineTest
{
public:
	MineTest() = default;
	~MineTest() = default;
	void run();
private:
	GLFWwindow *m_Window;
	uint m_FPS, m_UPS;

	void init();
	void render();
	void update();
	void tick();

	void preInit();
	void postInit();

};

