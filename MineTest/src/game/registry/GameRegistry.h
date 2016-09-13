#pragma once
#include "../../Defines.h"
#include "../player/Player.h"
#include <vector>
#include <iostream>

struct BlockDefinition
{
	std::string regName;
	uint ID;
	
	BlockDefinition(std::string regName, uint ID) : regName(regName), ID(ID) {}
};

class GameRegistry
{
public:
	static GameRegistry& instance();

public:
	~GameRegistry() = default;

	inline Player& getPlayer() { return player; }

	//Blocks
	void registerBlock(std::string regName);
	uint numRegisteredBLocks();
	const BlockDefinition& getBlockDefByID(uint ID);
	const BlockDefinition& getBlockDefByRegName(std::string name);


	//void registerItem(const Item &item);

private:
	Player player;

	std::vector<BlockDefinition> m_RegisteredBlocks;
	//std::vector<Item> m_RegisteredItems;


	GameRegistry() = default;
	friend class BlockRenderer;
};

