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
	void HardDropBlock();
	bool gameOver;
	int score;
	Music music;

private:
	bool IsBlockOutside(Block block);
	void RotateBlock(bool IsClockwise);
	void LockBlock();
	bool BlockFits(Block block);
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	void UpdateGhostBlockRow();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	void HoldBlock();
	void SpawnNewBlock();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
	Block ghostBlock;
	Block holdBlock;
	Grid grid;
	Sound rotateSfx;
	Sound clearSfx;
	bool usedHold;
};
