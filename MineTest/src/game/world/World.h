#pragma once
#include "../../Defines.h"
#include "Chunk.h"
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include "../../util/FastNoise.h"

class World
{
public:
	World();
	~World();

	void create(uint seed);
	void render();
	void update();

	std::vector<Chunk>& getChunks();

protected:
	void registerChunk(Chunk& chunk);
	void createThread();

private:
	std::mutex m_ChunkMutex;
	std::vector<Chunk> m_LoadedChunks;
	FastNoise m_Noise;

	bool m_ThreadRunning;
	std::unique_ptr<std::thread> m_Thread;

};

