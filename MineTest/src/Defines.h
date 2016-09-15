#pragma once
#include "GL/glew.h"
#include <iostream>
#define DEBUG
#ifdef DEBUG
#define GLCall(x) \
				x; \
				__CheckGLError(#x, __FILE__, __LINE__);
#else
#define GLCall(x) x;
#endif

#pragma warning(disable:4244)
#pragma warning(disable:4101)
#pragma warning(disable:4099)
#pragma warning(disable:4305)


void __CheckGLError(const char* function, const char* file, int line);

typedef unsigned int uint;
typedef unsigned char byte;

constexpr int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;