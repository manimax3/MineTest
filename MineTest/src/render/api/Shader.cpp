#include "Shader.h"

#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm\gtc\type_ptr.hpp"

using namespace glm;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// If geometry shader is given, compile geometry shader
	GLuint geometry;
	if (geometryPath != nullptr)
	{
		const GLchar * gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "GEOMETRY");
	}
	// Shader Program
	this->m_Program = glCreateProgram();
	glAttachShader(this->m_Program, vertex);
	glAttachShader(this->m_Program, fragment);
	if (geometryPath != nullptr)
		glAttachShader(this->m_Program, geometry);
	glLinkProgram(this->m_Program);
	checkCompileErrors(this->m_Program, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessary
	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
	if (geometryPath != nullptr)
		GLCall(glDeleteShader(geometry));

}
#pragma region "Uniform setters"
void Shader::setUniform1f(const GLchar* name, float value)
{
	GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform1fv(const GLchar* name, float* value, int count)
{
	GLCall(glUniform1fv(getUniformLocation(name), count, value));
}

void Shader::setUniform1i(const GLchar* name, int value)
{
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1iv(const GLchar* name, int* value, int count)
{
	GLCall(glUniform1iv(getUniformLocation(name), count, value));
}

void Shader::setUniform2f(const GLchar* name, const vec2& vector)
{
	GLCall(glUniform2f(getUniformLocation(name), vector.x, vector.y));
}

void Shader::setUniform3f(const GLchar* name, const vec3& vector)
{
	GLCall(glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z));
}

void Shader::setUniform4f(const GLchar* name, const vec4& vector)
{
	GLCall(glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
}

void Shader::setUniformMat4(const GLchar* name, const mat4& matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value_ptr(matrix)));
}
#pragma endregion
GLint Shader::getUniformLocation(const GLchar* name)
{
	if (locations.size() > 0)
	{
		for (auto &loc : locations)
		{
			if (loc.m_Name == name)
			{
				return loc.m_Location;
			}
		}
	}
	GLint location = glGetUniformLocation(m_Program, name);
	UniformLoc loc;
	loc.m_Location = location;
	loc.m_Name = name;
	locations.push_back(loc);
	return location;
}
void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
		}
	}
}