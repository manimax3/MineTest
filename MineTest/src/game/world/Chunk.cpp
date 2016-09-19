#include "Chunk.h"
#include <fstream>
#include <iosfwd>

#define HEADER_SIZE_BYTES (sizeof(header))
#define DATA_SIZE_BYTES ((sizeof(Block) * m_Blocks.size()) + 3 * sizeof(int))

struct FileHeader {
	char title[4] = { 'M', 'T', 'C', 'S' };
	short major = 0;
	short minor = 0;
} header;


Chunk::Chunk(int x, int z, ChunkHeightProvider provider)
	: x(x), z(z)
{
	generate(provider);
}

void Chunk::unload()
{
	size_t numBlocks = m_Blocks.size();

	std::vector<char> data(HEADER_SIZE_BYTES + DATA_SIZE_BYTES + 4);

	std::memcpy(&data[0], &header, HEADER_SIZE_BYTES);
	std::memcpy(&data[HEADER_SIZE_BYTES                    ],	(&this->x), sizeof(int));
	std::memcpy(&data[HEADER_SIZE_BYTES + sizeof(int)      ],	(&this->z), sizeof(int));
	std::memcpy(&data[HEADER_SIZE_BYTES + (2 * sizeof(int))],	 &numBlocks, sizeof(int));
	std::memcpy(&data[HEADER_SIZE_BYTES + (3 * sizeof(int))],	 &this->m_Blocks[0], numBlocks * sizeof(Block));
	std::memcpy(&data[HEADER_SIZE_BYTES + DATA_SIZE_BYTES  ],	 "MTCS", 4);

	std::ofstream file;
	file.open(std::string("./data/chunks/") + std::to_string(this->x) + "-" + std::to_string(this->z) + ".mtcs", 
		std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.is_open())
	{
		file.write(&data[0], data.size());
	}
}

void Chunk::generate(ChunkHeightProvider provider)
{
	for (short dx = 0; dx < 16; dx++)
		for (short dy = 0; dy < 16; dy++)
		{
			float finalX = dx + (this->x << 4);
			float finalZ = dy + (this->z << 4);
			float finalY = std::floorf(provider.GetSimplex(finalX, finalZ) * 10);
			this->m_Blocks.emplace_back(GameRegistry::instance().getBlockDefByID(0), glm::vec3(dx, finalY, dy));
		}
}


