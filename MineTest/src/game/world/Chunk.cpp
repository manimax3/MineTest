#include "Chunk.h"



Chunk::Chunk(int x, int z, ChunkHeightProvider provider)
	: x(x), z(z)
{
	generate(provider);
}

void Chunk::generate(ChunkHeightProvider provider)
{
	for (short dx = 0; dx < 16; dx++)
		for (short dy = 0; dy < 16; dy++)
		{
			float finalX = dx + (this->x << 4);
			float finalZ = dy + (this->z << 4);
			float finalY = std::floorf(provider.GetSimplex(finalX, finalZ) * 10);
			this->m_Blocks.emplace_back(GameRegistry::instance().getBlockDefByID(0), glm::vec3(finalX, finalY, finalZ));
		}
}


