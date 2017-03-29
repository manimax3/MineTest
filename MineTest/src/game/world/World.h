#pragma once
#include "../../Defines.h"
#include "Chunk.h"
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include "../../util/FastNoise.h"
#include <deque>

typedef FastNoise ChunkHeightProvider;
typedef std::unique_ptr<Chunk> ChunkPointer;

class World
{
public:
	World();
	~World();

	void render();
	void update();

	std::vector<ChunkPointer>& getChunks();

private:
	std::mutex m_ChunkMutex;
	std::vector<ChunkPointer> m_LoadedChunks;
	FastNoise m_Noise;

	bool m_ThreadRunning;

	void startRegionGeneration();

};

