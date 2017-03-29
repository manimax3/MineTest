#include "Defines.h"

void __CheckGLError(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return;
	while (error != GL_NO_ERROR)
	{
		std::cout << "[ERROR] " << "( " << error << " )" << " >>" << function << "<< IN LINE: " << line << "IN FILE: " << file << std::endl;
		error = glGetError();
	}
}

bool does_file_exist(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}