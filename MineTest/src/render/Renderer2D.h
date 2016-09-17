#pragma once

#include "../Defines.h"
#include "api/Texture2D.h"
#include "api/Shader.h"
#include "../gui/Font.h"

struct VertexData
{
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 texcoords;
	float tid;
};

constexpr int RENDERER_VERTEX_SIZE = sizeof(VertexData);
constexpr int RENDERER_MAX_SPRITES = 60000;
constexpr int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
constexpr int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
constexpr int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

class Renderer2D
{
public:
	static Renderer2D* instance();
	~Renderer2D();
public:
	void init();
	void begin();

	void submitText(std::string text, glm::vec2 position, Font& font, glm::vec3 color);
	void submitRectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color);
	void submitRectangle(glm::vec2 position, glm::vec2 size, glm::vec2 texCoord = glm::vec2(0,0), int tid = 0);

	int addTexture(Texture2D *texture);
	int queryTexture(uint id);

	void flush();

private:
	void setTexture(uint id);

	Renderer2D() = default;

	std::unique_ptr<Shader> m_Shader;
	std::vector<Texture2D*> m_Textures;
	uint m_Buffer, vbo;
	uint m_IndexCount;

	VertexData* buffer;
};


