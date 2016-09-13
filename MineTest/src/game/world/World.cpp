#include "World.h"

#include "../../render/BlockRenderer.h"


World::World()
{
	m_Noise.SetInterp(FastNoise::Interp::Linear);
	this->getChunks().clear();
	this->getChunks().shrink_to_fit();
}


World::~World()
{
	m_Thread->join();
}

void World::render()
{
	std::lock_guard<std::mutex> lock(m_ChunkMutex);
	for (auto &loadedChunk : this->getChunks())
	{
		BlockRenderer::instance().begin();
		BlockRenderer::instance().render(loadedChunk);
	}
}

void World::update()
{
	//Todo do this stuff in extra thread so
	//and also some more efficient "what do i neeed to update" checking which is currently not present
	if (!m_ThreadRunning)
		this->createThread();
// 	m_ChunkMutex.lock();
// 	this->getChunks().clear();
// 	this->getChunks().shrink_to_fit();
// 	m_ChunkMutex.unlock();
// 	int playerChunkzPos = ((int)GameRegistry::instance().getPlayer().getPosition().z) >> 4;
// 	int playerChunkXPos = ((int)GameRegistry::instance().getPlayer().getPosition().x) >> 4;
// 	for (short dx = -3; dx < 3; dx++)
// 		for (short dz = -3; dz < 3; dz++)
// 		{
// 			this->getChunks().emplace_back();
// 			for (short x = 0; x < 16; x++)
// 				for (short y = 0; y < 16; y++)
// 				{
// 					float finalX = x + ((playerChunkXPos + dx) << 4);
// 					float finalZ = y + ((playerChunkzPos + dz) << 4);
// 					float finalY = m_Noise.GetSimplex(finalX, finalZ) * 10;
// 					this->getChunks().back().m_Blocks.emplace_back(GameRegistry::instance().getBlockDefByID(0), glm::vec3(finalX, finalY, finalZ));
// 				}
// 		}

}

std::vector<Chunk>& World::getChunks()
{
	//std::lock_guard<std::mutex> lock(m_ChunkMutex);
	return m_LoadedChunks;
}

void World::registerChunk(Chunk& chunk)
{
	std::lock_guard<std::mutex> lock(m_ChunkMutex);
	m_LoadedChunks.push_back(std::move(chunk));
}

void World::createThread()
{
	m_ThreadRunning = true;
	m_Thread = std::make_unique<std::thread>([this]() {
		while (true)
		{
			m_ChunkMutex.lock();
			this->getChunks().clear();
			this->getChunks().shrink_to_fit();
			int playerChunkzPos = ((int)GameRegistry::instance().getPlayer().getPosition().z) >> 4;
			int playerChunkXPos = ((int)GameRegistry::instance().getPlayer().getPosition().x) >> 4;
			for (short dx = -3; dx < 3; dx++)
				for (short dz = -3; dz < 3; dz++)
				{
					this->getChunks().emplace_back();
					for (short x = 0; x < 16; x++)
						for (short y = 0; y < 16; y++)
						{
							float finalX = x + ((playerChunkXPos + dx) << 4);
							float finalZ = y + ((playerChunkzPos + dz) << 4);
							float finalY = m_Noise.GetSimplex(finalX, finalZ) * 10;
							this->getChunks().back().m_Blocks.emplace_back(GameRegistry::instance().getBlockDefByID(0), glm::vec3(finalX, finalY, finalZ));
						}
				}
			m_ChunkMutex.unlock();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		

	});
}