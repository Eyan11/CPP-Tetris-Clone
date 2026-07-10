#pragma once

#include <vector>
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	Grid grid;

private:
	bool IsBlockOutside();
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks;
	Block curBlock;
	Block nextBlock;
};
