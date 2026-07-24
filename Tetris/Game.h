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
	void MoveBlockDown(bool isSoftDrop);
	void HardDropBlock();
	void Update();
	bool gameOver;
	Music music;

private:
	void RotateBlock(bool IsClockwise);
	void LockBlock(bool forceLock);
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	void UpdateGhostBlockRow();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	void HoldBlock();
	void SpawnNewBlock();
	bool BlockFits(Block block, int rowOffset, int colOffset);
	bool UpdateIsBlockGrounded();
	std::vector<Block> blocks; // The pool of blocks to randomly choose from
	Block curBlock;
	Block nextBlock;
	Block ghostBlock;
	Block holdBlock;
	bool usedHold;
	Grid grid;
	Sound rotateSfx;
	Sound clearSfx;
	Sound levelUpSfx;
	Sound hardDropSfx;

	// Locking
	float lockDelay; // Delay in seconds before locking block in place after it hits the floor
	double groundedTime;
	int numLockMoves; // Track the number of moves/rotations made by the current block while on the floor
	int maxLockMoves; // Maximum number of moves/rotations allowed while on the floor before locking
	bool isBlockGrounded; // Track whether the current block is grounded (touching the floor or another block)

	// Stats
	int linesCleared;
	int curLevel;
	int score;
	int highScore;

	// Timers
	int minutesElapsed;
	float secondsElapsed;
	double gravityTimer;
	double gravityInterval; // Time interval for automatic downward movement of the block
	double downInputTimer;
	double leftInputTimer;
	double rightInputTimer;
	float sideInputDelay; // Delay in seconds before allowing repeated left/right movement when holding the key (down input does not have a delay)
	float inputInterval; // Time interval for repeated left/right/down movements when holding the key
	double lastUpdateTime;

	// Text
	Font font;
	int fontSize;
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
