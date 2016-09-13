#pragma once
#include "../../Defines.h"
#include "glm/glm.hpp"
#include <vector>

struct UniformLoc {
	int m_Location;
	const char* m_Name;
};

class Shader
{
private:
	uint m_Program;
	std::vector<UniformLoc> locations;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	inline void Use() { GLCall(glUseProgram(m_Program)); }

	void setUniform1f(const GLchar* name, GLfloat value);
	void setUniform1fv(const GLchar* name, float* value, int count);
	void setUniform1i(const GLchar* name, int value);
	void setUniform1iv(const GLchar* name, int* value, int count);
	void setUniform2f(const GLchar* name, const glm::vec2& vector);
	void setUniform3f(const GLchar* name, const glm::vec3& vector);
	void setUniform4f(const GLchar* name, const glm::vec4& vector);
	void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
private:
	void checkCompileErrors(GLuint shader, std::string type);
	int getUniformLocation(const GLchar* name);
};