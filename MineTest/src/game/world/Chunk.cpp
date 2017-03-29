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


Chunk::Chunk(int x, int z, ChunkHeightProvider &provider)
	: x(x), z(z), provider(provider)
{
	relX = (((int) GameRegistry::instance().getPlayer().getPosition().x) >> 4) - x;
	relZ = (((int)GameRegistry::instance().getPlayer().getPosition().z) >> 4) - z;
	m_ShoudRegen = true;
}

void Chunk::update()
{
	if (!(x == (((int)GameRegistry::instance().getPlayer().getPosition().x) >> 4) - relX
		&& z == (((int)GameRegistry::instance().getPlayer().getPosition().z) >> 4) - relZ))
		m_ShoudRegen = true;
}

std::vector<Block>& Chunk::getBlocks()
{
	std::lock_guard<std::mutex> guard(m_BlockLock);
	return m_Blocks;
}

std::vector<Block>& Chunk::getBlocksUnlocked()
{
	return m_Blocks;
}

void Chunk::lock()
{
	m_BlockLock.lock();
}

void Chunk::unlock()
{
	m_BlockLock.unlock();
}

void Chunk::generate()
{
	if (!m_BlockLock.try_lock())
		return;

	this->m_Blocks.clear();

	int _X = (((int)GameRegistry::instance().getPlayer().getPosition().x) >> 4) - relX;
	int _Z = (((int)GameRegistry::instance().getPlayer().getPosition().z) >> 4) - relZ;

	for (short dx = 0; dx < 16; dx++)
		for (short dy = 0; dy < 16; dy++)
		{
			float finalX = dx + (_X << 4);
			float finalZ = dy + (_Z << 4);
			float finalY = std::floorf(provider.GetSimplex(finalX, finalZ) * 10);
			this->m_Blocks.emplace_back(GameRegistry::instance().getBlockDefByID(1), glm::vec3(dx, finalY, dy));
		}
	this->x = _X;
	this->z = _Z;

	m_BlockLock.unlock();
	m_ShoudRegen = false;
}

struct MTRS_HEADER
{
	char title[4] = { 'M', 'T', 'C', 'S' };
	char amountblocks;
};

//void Chunk::generate()
//{
//	int regX = this->x >> CHUNKS_PER_REGION_LOG2;
//	int regZ = this->z >> CHUNKS_PER_REGION_LOG2;
//	std::string regName = std::to_string(regX) + "," + std::to_string(regZ);
//
//	if (does_file_exist("/data/chunks/" + regName + ".mtrs"))
//	{
//		std::fstream file("/data/chunks/" + regName + ".mtrs",std::ios::binary);
//		file.seekg(0, file.end);
//		int length = file.tellg();
//		file.seekg(0, file.beg);
//
//		std::vector<char> data(length);
//		file.read(&data[0], length);
//		file.close();
//
//		char *title = new char[4]; std::memcpy(title, &data[0], 4); assert(strcmp(title, "MTRS") == 0);
//		int cX = static_cast<int>(data[5]); int cZ = static_cast<int>(data[6]);
//
//		if (cX + regX == this->x && cZ + regZ == this->z)
//		{
//			//Chunk found
//			std::memcpy(title, &data[7], 4);
//			int amountblocks = reinterpret_cast<int>(title); 
//		}
//		else {
//
//		}
//		delete title;
//
//	}
//	else
//	{
//
//	}
//
//}

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
