#pragma once
#include "../Defines.h"
#include "api/Texture2DArray.h"
#include "api/Shader.h"
#include "../game/world/Chunk.h"

class BlockRenderer
{

	static constexpr size_t CHUNK_VBO_MAX_SIZE = Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * Chunk::CHUNK_HEIGHT * sizeof(GLfloat) * 4;

public:
	static BlockRenderer* instance();
public:
	~BlockRenderer();

	void init();

	void begin();
	void render(const Chunk &chunk);

private:
	BlockRenderer();

	std::unique_ptr<Shader> m_Shader;
	Texture2DArray m_BlockTextures;

	uint m_ChunkVao;
	uint m_ChunkVBO;
};

