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
	bool gameOver;

private:
	bool IsBlockOutside();
	void RotateBlock(bool IsClockwise);
	void LockBlock();
	bool BlockFits();
	void Reset();
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
};
