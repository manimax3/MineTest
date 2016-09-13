#include "GameRegistry.h"

GameRegistry& GameRegistry::instance()
{
	static GameRegistry* instance = new GameRegistry;
	return *instance;
}

void GameRegistry::registerBlock(std::string regName)
{
	for (auto& bl : m_RegisteredBlocks)
		if (bl.regName == regName)
			return;

	this->m_RegisteredBlocks.emplace_back(regName, m_RegisteredBlocks.size());
	m_RegisteredBlocks.shrink_to_fit();
	std::cout << "Registered Block: " << regName.c_str() << std::endl;
}

uint GameRegistry::numRegisteredBLocks()
{
	return m_RegisteredBlocks.size();
}

const BlockDefinition& GameRegistry::getBlockDefByID(uint ID)
{
	return m_RegisteredBlocks[ID];
}

const BlockDefinition& GameRegistry::getBlockDefByRegName(std::string name)
{
	for (auto& block : m_RegisteredBlocks)
	{
		if (block.regName == name)
			return block;
	}
	registerBlock(name);
	return getBlockDefByRegName(name);
}

//void GameRegistry::registerItem(const Item &item)
//{
//	this->m_RegisteredItems.push_back(item);
//}
