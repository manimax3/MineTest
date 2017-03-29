#include "MineTest.h"
#include "./util/Timer.h"
#include "game/registry/GameRegistry.h"
#include "render/BlockRenderer.h"
#include "util/Input.h"
#include <iostream>
#include <assert.h>
#include <string>
#include "game/world/World.h"
#include "render/Renderer2D.h"
#include "gui/GroupManager.h"
#include "gui/debug/DebugGroup.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void MineTest::run()
{
	init();

	Timer* timer = new Timer;
	float time = 0.f;
	float updateTimer = 0.f;
	float updateTick = 1.f / 60.f;
	uint frames = 0;
	uint updates = 0;

	while (!glfwWindowShouldClose(m_Window))
	{
		if (timer->elapsed() - updateTimer > updateTick)
		{
			update();
			updates++;
			updateTimer += updateTick;
		}
		{
			render();
			frames++;
		}
		if (timer->elapsed() - time > 1.f)
		{
			time += 1.0f;
			m_FPS = frames;
			m_UPS = updates;
			frames = 0;
			updates = 0;
			tick();
		}
	}


	glfwTerminate();
}

void MineTest::init()
{
	preInit();


	assert(glfwInit());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MineTest", NULL, NULL);
	assert(m_Window);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(0);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGetError();
	std::cout << "Using OpenGL " << std::string(reinterpret_cast<char*>(const_cast<byte*>(glGetString(GL_VERSION)))) << std::endl;
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	glEnable(GL_DEPTH_TEST);
	postInit();
}

World *world;
void MineTest::render()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	render3D();
	render2D();

	glfwSwapBuffers(m_Window);
}

void MineTest::update()
{
	glfwPollEvents();
	GameRegistry::instance().getPlayer().update();
	world->update();
	GroupManager::instance()->update();
}
DebugGroup *debug;
void MineTest::tick()
{
#ifdef DEBUG
	//std::cout << "FPS: " << m_FPS << " UPS: " << m_UPS << std::endl;
#endif

}

void MineTest::preInit()
{
	GameRegistry::instance().registerBlock(std::string("block_Sided"));
	GameRegistry::instance().registerBlock(std::string("block_Dirt"));
}

void MineTest::postInit()
{

	BlockRenderer::instance()->init();
	Renderer2D::instance()->init();
	debug = new DebugGroup(m_FPS, m_UPS);
	world = new World;
}

void MineTest::render3D()
{
	world->render();
}

void MineTest::render2D()
{
	Renderer2D::instance()->begin();
	GroupManager::instance()->render();
	Renderer2D::instance()->flush();
}

#pragma region Callbacks

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xOffset = xpos - Input::instance().m_MouseX;
	float yOffset = -ypos + Input::instance().m_MouseY;

	Input::instance().m_MouseX = xpos;
	Input::instance().m_MouseY = ypos;

	GameRegistry::instance().getPlayer().m_Camera.calculateRotation(xOffset, yOffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
	{
		Input::instance().keys[key] = true;
		Input::instance().mousePressed(key);
	}
	else if (action == GLFW_RELEASE)
	{
		Input::instance().keys[key] = false;
		Input::instance().mouseReleased(key);
		if (key == GLFW_KEY_F4)
			for (auto &ch : world->getChunks())
				ch->unload();
	}
}

#pragma endregion