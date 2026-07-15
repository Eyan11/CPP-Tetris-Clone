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
	void MoveBlockDown(bool isSoftDrop = false, bool isHardDrop = false);
	void MoveBlockToFloor();
	Grid grid;
	bool gameOver;
	int score;

private:
	bool IsBlockOutside();
	void RotateBlock(bool IsClockwise);
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
};
