#pragma once
#include "../../Defines.h"
#include "../registry/GameRegistry.h"
#include "glm/glm.hpp"
#include <vector>

struct Block
{
	uint ID;
	glm::vec3 position;
	bool visible;

	Block(const BlockDefinition &def) : ID(def.ID) {}
	Block(const BlockDefinition &def, glm::vec3 position) : ID(def.ID), position(position) {}
};

class Chunk
{
private:
	static const uint CHUNK_SIZE = 16;
	static const uint CHUNK_HEIGHT = 256;
public:
	Chunk() = default;
	~Chunk() = default;
	std::vector<Block> m_Blocks;
private:
	friend class BlockRenderer;
};

