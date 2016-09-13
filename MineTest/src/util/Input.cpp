#include "Input.h"
#include "../game/registry/GameRegistry.h"
#include "GLFW/glfw3.h"

Input& Input::instance()
{
	static Input *instance = new Input;
	return *instance;
}

Input::Input()
{
	for (int i = 0; i < 1024; ++i)
		keys[i] = false;
}


