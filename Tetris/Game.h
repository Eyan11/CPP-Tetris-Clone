#pragma once

#include <vector>
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void HandleInput();
	bool MoveBlockDown(bool isSoftDrop, bool isHardDrop);
	void MoveBlockToFloor();
	bool gameOver;
	int score;
	Music music;

private:
	bool IsBlockOutside();
	void RotateBlock(bool IsClockwise);
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
	Grid grid;
	Sound rotateSfx;
	Sound clearSfx;
};
