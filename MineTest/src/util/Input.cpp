#include "Input.h"
#include "../game/registry/GameRegistry.h"
#include "GLFW/glfw3.h"

Input& Input::instance()
{
	static Input *instance = new Input;
	return *instance;
}


void Input::registerListener(IKeyListener* listener)
{
	m_Listeners.push_back(listener);
}


void Input::mousePressed(int key)
{
	for (auto &li : m_Listeners)
		li->onKeyPressed(key);
}


void Input::mouseReleased(int key)
{
	for (auto &li : m_Listeners)
		li->onKeyReleased(key);
}

Input::Input()
{
	for (int i = 0; i < 1024; ++i)
		keys[i] = false;
}

