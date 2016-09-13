#pragma once
#include "../../Defines.h"

struct TextureProperties
{
	int width, height;
	GLenum Wrapping_S;
	GLenum Wrapping_T;
	GLenum FilterMin;
	GLenum FilterMag;
	bool genMipMaps;
};