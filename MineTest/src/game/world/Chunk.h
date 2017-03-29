#pragma once
#include "../../Defines.h"
#include "../registry/GameRegistry.h"
#include "../../util/FastNoise.h"
#include <atomic>
#include <mutex>

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
	static constexpr uint CHUNKS_PER_REGION_LOG2 = 2;
public:
	Chunk(int x, int z, ChunkHeightProvider &provider);
	~Chunk() = default;

	void unload();
	void update();
	std::vector<Block>& getBlocks();

	int x, z;
	std::atomic_bool m_ShoudRegen;
	void generate();
private:

	ChunkHeightProvider &provider;
	std::vector<Block> m_Blocks;
	int relX, relZ;

	std::mutex m_BlockLock;
};