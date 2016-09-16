#include "Renderer2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "freetype-gl.h"

using namespace ftgl;

glm::mat4 projection = glm::ortho(0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.f, -1.f, 1.f);

Renderer2D* Renderer2D::instance()
{
	static Renderer2D* instance = new Renderer2D;
	return instance;
}

void Renderer2D::init()
{
	uint ebo;
	m_Shader = std::make_unique<Shader>("./res/shader/Renderer2D.vert", "./res/shader/Renderer2D.frag");

	uint* indices = new uint[RENDERER_INDICES_SIZE];

	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	GLCall(glCreateBuffers(1, &vbo));
	GLCall(glCreateBuffers(1, &ebo));
	GLCall(glCreateVertexArrays(1, &m_Buffer));
	
	GLCall(glBindVertexArray(m_Buffer));
		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW));
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat))));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat))));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat))));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, indices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(0));


}

void Renderer2D::submitRectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color)
{
	buffer->position = position;
	buffer->color = color;
	buffer->texcoords = position;
	buffer->tid = 32;
	buffer++;

	glm::vec2 vert = glm::vec2(position.x, position.y + size.y);
	buffer->position = vert;
	buffer->color = color;
	buffer->texcoords = position;
	buffer->tid = 32;
	buffer++;

	vert = position + size;
	buffer->position = vert;
	buffer->color = color;
	buffer->texcoords = position;
	buffer->tid = 32;
	buffer++;

	vert = glm::vec2(position.x + size.x, position.y);
	buffer->position = vert;
	buffer->color = color;
	buffer->texcoords = position;
	buffer->tid = 32;
	buffer++;

	m_IndexCount += 6;
}

int Renderer2D::addTexture(Texture2D *texture)
{
	m_Textures.push_back(texture);
	assert(m_Textures.size() <= 32);
	return m_Textures.size() - 1;
}


void Renderer2D::flush()
{
	GLCall(glUnmapNamedBuffer(vbo));
	GLCall(glBindVertexArray(m_Buffer));
	GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));
}

void Renderer2D::begin()
{
	m_Shader->Use();
	
	int texs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
	for (int i = 0; i < m_Textures.size(); i++)
		m_Textures.at(i)->bind(i);
	m_Shader->setUniform1iv("textures", &texs[0], 30);
	m_Shader->setUniformMat4("projection", projection);
	m_IndexCount = 0;
	buffer = (VertexData*) glMapNamedBuffer(vbo, GL_WRITE_ONLY);
}