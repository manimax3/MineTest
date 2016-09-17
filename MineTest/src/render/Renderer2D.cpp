#include "Renderer2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include <sstream>
#include "freetype-gl/freetype-gl.h"
#include "../gui/FontManager.h"

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

	std::cout << "2D Renderer Initialized!" << std::endl;
}

void Renderer2D::begin()
{
	m_Shader->Use();
	m_Shader->setUniform1i("textures", 0);
	m_Shader->setUniformMat4("projection", projection);
	m_IndexCount = 0;
	buffer = (VertexData*) glMapNamedBuffer(vbo, GL_WRITE_ONLY);
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

void Renderer2D::submitRectangle(glm::vec2 position, glm::vec2 size, glm::vec2 texCoord, int tid)
{
	buffer->position = position;
	buffer->color = glm::vec3(0.0);
	buffer->texcoords = texCoord;
	buffer->tid = tid;
	buffer++;

	glm::vec2 vert = glm::vec2(position.x, position.y + size.y);
	glm::vec2 uv = glm::vec2(texCoord.x, texCoord.y + 1.f);
	buffer->position = vert;
	buffer->color = glm::vec3(0.0);;
	buffer->texcoords = uv;
	buffer->tid = tid;
	buffer++;

	vert = position + size;
	uv = texCoord + glm::vec2(1,1);
	buffer->position = vert;
	buffer->color = glm::vec3(0.0);;
	buffer->texcoords = uv;
	buffer->tid = tid;
	buffer++;

	vert = glm::vec2(position.x + size.x, position.y);
	uv = glm::vec2(texCoord.x + 1.f, texCoord.y);
	buffer->position = vert;
	buffer->color = glm::vec3(0.0);;
	buffer->texcoords = uv;
	buffer->tid = tid;
	buffer++;

	m_IndexCount += 6;
}

void Renderer2D::submitText(std::string text, glm::vec2 position, Font& font, glm::vec3 color)
{
	using namespace ftgl;
	m_Shader->setUniform1f("isText", 1.0f);
	setTexture(font.getID());
	const glm::vec2 &scale = font.getScale();
	float x = position.x;
	texture_font_t* ftFont = font.getFTFont();

	for (uint i = 0; i < text.length(); i++)
	{
		char c = text[i];
		texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
		if (glyph != nullptr)
		{
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			    x += kerning / scale.x;
			}

			float x0 = x + glyph->offset_x / scale.x;
			float y0 = position.y - glyph->offset_y / scale.y;
			float x1 = x0 + glyph->width / scale.x;
			float y1 = y0 + glyph->height / scale.y;
			
			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			buffer->position = glm::vec2(x0, y0);
			buffer->color = color;
			buffer->texcoords = glm::vec2(u0, v0);
			buffer->tid = 0;
			buffer++;

			buffer->position = glm::vec2(x0, y1);
			buffer->color = color;
			buffer->texcoords = glm::vec2(u0, v1);
			buffer->tid = 0;
			buffer++;

			buffer->position = glm::vec2(x1, y1);
			buffer->color = color;
			buffer->texcoords = glm::vec2(u1, v1);
			buffer->tid = 0;
			buffer++;

			buffer->position = glm::vec2(x1, y0);
			buffer->color = color;
			buffer->texcoords = glm::vec2(u1, v0);
			buffer->tid = 0;
			buffer++;

			m_IndexCount += 6;

			x += glyph->advance_x / scale.x;
		}
	}
	this->flush();
	this->begin();
	m_Shader->setUniform1f("isText", 0.0f);
}

int Renderer2D::addTexture(Texture2D *texture)
{
	m_Textures.push_back(texture);
	assert(m_Textures.size() <= 32);
	return m_Textures.size() - 1;
}


int Renderer2D::queryTexture(uint id)
{
	for (int i = 0; i < m_Textures.size(); i++)
	{
		if (m_Textures.at(i)->getID() == id)
			return i;
	}
	return 0;
}

void Renderer2D::setTexture(uint id)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Renderer2D::flush()
{
	GLCall(glUnmapNamedBuffer(vbo));
	GLCall(glBindVertexArray(m_Buffer));
	GLCall(glDepthFunc(GL_ALWAYS));
	GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));
	GLCall(glDepthFunc(GL_LESS));
}
