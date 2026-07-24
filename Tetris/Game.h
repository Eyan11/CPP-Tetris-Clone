#pragma once

#include <vector>
#include "grid.h"
#include "blocks.cpp"
#include "TextUI.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight);
	~Game();
	void Draw();
	void HandleInput();
	bool MoveBlockDown(bool isSoftDrop, bool isHardDrop);
	void HardDropBlock();
	void Update();
	bool gameOver;
	Music music;

private:
	bool IsBlockOutside(Block block);
	void RotateBlock(bool IsClockwise);
	void LockBlock(bool forceLock);
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
	bool IsBlockGrounded();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
	Block ghostBlock;
	Block holdBlock;
	Grid grid;
	Sound rotateSfx;
	Sound clearSfx;
	bool usedHold;
	float lockDelay; // Delay in seconds before locking block in place after it hits the floor
	double lockStartTime; // Time when the current block first hit the floor
	int numLockMoves; // Track the number of moves/rotations made by the current block while on the floor
	int maxLockMoves; // Maximum number of moves/rotations allowed while on the floor before locking
	bool isBlockGrounded; // Track whether the current block is grounded (touching the floor or another block)

	// Stats
	int linesCleared;
	int curLevel;
	int score;
	int highScore;
	int minutesElapsed;
	float secondsElapsed;
	double gravityTimer;
	double gravityInterval; // Time interval for automatic downward movement of the block
	double lastUpdateTime;

	// Text
	Font font;
	TextUI nextText;
	TextUI timeHeaderText;
	TextUI timeText;
	TextUI scoreHeaderText;
	TextUI scoreText;
	TextUI highScoreHeaderText;
	TextUI highScoreText;
	TextUI holdText;
	TextUI levelHeaderText;
	TextUI levelText;
	TextUI linesHeaderText;
	TextUI linesText;
	TextUI gameOverText;
	Vector2 nextBlockAnchorPos;
	Vector2 holdBlockAnchorPos;
	Vector2 gridAnchorPos;
};
