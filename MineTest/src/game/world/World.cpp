#include "World.h"

#include "../../render/BlockRenderer.h"


World::World()
{
	m_Noise.SetInterp(FastNoise::Interp::Linear);
	for (int x = -3; x < 3; x++)
		for (int z = -3; z < 3; z++)
			m_LoadedChunks.push_back(std::make_unique<Chunk>(x, z, m_Noise));

	startRegionGeneration();
		

}


World::~World()
{}

void World::render()
{
	BlockRenderer::instance()->begin();
	for (auto &loadedChunk : this->getChunks())
	{
		BlockRenderer::instance()->render(*loadedChunk);
	}
}

void World::update()
{
	for (auto& chunk : m_LoadedChunks)
		chunk->update();
}

std::vector<ChunkPointer>& World::getChunks()
{
	return m_LoadedChunks;
}

void World::startRegionGeneration()
{
	std::thread thread([this]() {
		while (true)
		{
			for (auto &chunk : m_LoadedChunks)
				if (chunk->m_ShoudRegen)
					chunk->generate();
		}
	});
	thread.detach();
}

