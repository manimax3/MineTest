#pragma once
#include "../../Defines.h"
#include "../registry/GameRegistry.h"
#include "../../util/FastNoise.h"

typedef FastNoise ChunkHeightProvider;

struct Block
{
	short ID;
	glm::vec3 position;

	Block(const BlockDefinition &def) : ID(def.ID) {}
	Block(const BlockDefinition &def, glm::vec3 position) : ID(def.ID), position(position) {}
};

class Chunk
{
public:
	static constexpr uint CHUNK_SIZE = 16;
	static constexpr uint CHUNK_HEIGHT = 256;
public:
	Chunk(int x, int z, ChunkHeightProvider provider);
	~Chunk() = default;

	void unload();

	std::vector<Block> m_Blocks;
	int x, z;
private:
	void generate(ChunkHeightProvider provider);
};

