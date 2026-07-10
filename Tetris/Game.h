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
	void MoveBlockToFloor();
	Grid grid;

private:
	bool IsBlockOutside();
	void RotateBlock(bool IsClockwise);
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks;
	Block curBlock;
	Block nextBlock;
};
