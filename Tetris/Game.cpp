#include <random>
#include <iostream>
#include "Game.h"

Game::Game(int windowWidth, int windowHeight) // Constructor
{
	grid = Grid();
	grid.CenterGridInWindow(windowWidth, windowHeight);
	blocks = GetAllBlocks();
	gameOver = false;
	score = 0;
	usedHold = false;

	nextBlock = GetRandomBlock();
	holdBlock.isHoldBlock = true;
	holdBlock.isHoldBlockSet = false;
	SpawnNewBlock();

	// Sound
	InitAudioDevice();
	music = LoadMusicStream("Assets/Sounds/djartmusic-my-8-bit-hero.mp3");
	PlayMusicStream(music);
	SetMusicVolume(music, 0.2f);
	rotateSfx = LoadSound("Assets/Sounds/rotate.mp3");
	clearSfx = LoadSound("Assets/Sounds/clear.mp3");
	levelUpSfx = LoadSound("Assets/Sounds/level_up.mp3");
	hardDropSfx = LoadSound("Assets/Sounds/hard_drop.mp3");

	// Locking
	lockDelay = 0.5;
	numLockMoves = 0;
	maxLockMoves = 15;
	groundedTime = 0;
	isBlockGrounded = false;

	// Stats
	linesCleared = 0;
	curLevel = 1;
	score = 0;
	highScore = 0;

	// Timers
	minutesElapsed = 0;
	secondsElapsed = 0;
	gravityTimer = 0;
	gravityInterval = pow((0.8 - ((curLevel - 1) * 0.007)), curLevel - 1); // Gravity interval formula from NES Tetris))
	downInputTimer = 0;
	leftInputTimer = 0;
	rightInputTimer = 0;
	sideInputDelay = 0.2;
	inputInterval = 0.065;
	lastUpdateTime = GetTime();


	// *** UI
	gridAnchorPos = { grid.GetGridCoordinateX(true), grid.GetGridCoordinateY(true) };
	font = LoadFontEx("Assets/monogram.ttf", 64, 0, 0);
	int textSeparationX = 15;
	int textSeparationY = 35;

	Vector2 anchorPos = { grid.GetGridCoordinateX(false) + textSeparationX, gridAnchorPos.y };
	nextText = TextUI(font, "Next", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Top);
	nextBlockAnchorPos = { anchorPos.x, anchorPos.y + 50 };

	anchorPos.y = grid.GetGridCoordinateY(false);
	highScoreText = TextUI(font, "0", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	highScoreHeaderText = TextUI(font, "High Score", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	scoreText = TextUI(font, "0", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	scoreHeaderText = TextUI(font, "Score", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	timeText = TextUI(font, "00:00", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	timeHeaderText = TextUI(font, "Time", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Left, TextUI::VerticalAlignment::Bottom);
	
	anchorPos = { gridAnchorPos.x - textSeparationX, gridAnchorPos.y };
	holdText = TextUI(font, "Hold", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Right, TextUI::VerticalAlignment::Top);
	holdBlockAnchorPos = { anchorPos.x - (30 * 3), anchorPos.y + 50 };

	anchorPos.y = grid.GetGridCoordinateY(false);
	linesText = TextUI(font, "0", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Right, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	linesHeaderText = TextUI(font, "Lines", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Right, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	levelText = TextUI(font, "1", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Right, TextUI::VerticalAlignment::Bottom);

	anchorPos.y -= textSeparationY;
	levelHeaderText = TextUI(font, "Level", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Right, TextUI::VerticalAlignment::Bottom);

	anchorPos.y = gridAnchorPos.y - textSeparationY;
	anchorPos.x = gridAnchorPos.x + (grid.GetGridCoordinateX(false) - gridAnchorPos.x) / 2;
	gameOverText = TextUI(font, "GAME OVER", anchorPos, 38, 2, WHITE, TextUI::HorizontalAlignment::Center, TextUI::VerticalAlignment::Middle);
}

Game::~Game() // Destructor
{
	UnloadSound(rotateSfx);
	UnloadSound(clearSfx);
	UnloadSound(levelUpSfx);
	UnloadSound(hardDropSfx);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

// Returns a random block while garunteeing all blocks are given 
Block Game::GetRandomBlock()
{
	if (blocks.empty()) blocks = GetAllBlocks(); // Refill blocks when all used

	int randIndex = rand() % blocks.size(); // Get random value from 0-6
	Block block = blocks[randIndex];

	blocks.erase(blocks.begin() + randIndex); // Remove randomly chosen block to garuntee all blocks are given
	return block;
}

// Helper method to return all block types as a vector of blocks
std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

// Handles calling all draw methods for the game including grid, curBlock, ghostBlock, nextBlock, and holdBlock
void Game::Draw()
{
	grid.Draw();
	curBlock.Draw(gridAnchorPos.x, gridAnchorPos.y);
	if(!gameOver) ghostBlock.Draw(gridAnchorPos.x, gridAnchorPos.y);

	// Next Block
	nextText.Draw();
	switch (nextBlock.id) { // Make sure all block types are centered
		case 3: // I block
			nextBlock.Draw(nextBlockAnchorPos.x, nextBlockAnchorPos.y - 15);
			break;
		case 4: // O block
			nextBlock.Draw(nextBlockAnchorPos.x + 15, nextBlockAnchorPos.y);
			break;
		default:
			nextBlock.Draw(nextBlockAnchorPos.x, nextBlockAnchorPos.y);
			break;
	}

	// Hold Block
	holdText.Draw();
	if (holdBlock.isHoldBlockSet) {
		switch (holdBlock.id) { // Make sure all block types are centered
			case 3: // I block
				holdBlock.Draw(holdBlockAnchorPos.x - 30, holdBlockAnchorPos.y - 15);
				break;
			case 4: // O block
				holdBlock.Draw(holdBlockAnchorPos.x + 15, holdBlockAnchorPos.y);
				break;
			default:
				holdBlock.Draw(holdBlockAnchorPos.x, holdBlockAnchorPos.y);
				break;
		}
	}


	levelText.Draw();
	levelHeaderText.Draw();
	linesText.Draw();
	linesHeaderText.Draw();
	timeText.Draw();
	timeHeaderText.Draw();
	scoreText.Draw();
	scoreHeaderText.Draw();
	highScoreText.Draw();
	highScoreHeaderText.Draw();
	if (gameOver) gameOverText.Draw();
}

// Checks for input and calls respective method to handle it
void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) { // Restart game
		Reset();
		return;
	}

	if (gameOver) return; // Prevent input when game is over
	
	// *** On Input Pressed (the first frame of the input)
	switch (keyPressed) 
	{
		case KEY_LEFT: // Move block left 1 cell
			MoveBlockLeft();
			leftInputTimer = GetTime() - lastUpdateTime;
			break;
		case KEY_RIGHT: // Move block right 1 cell
			MoveBlockRight();
			rightInputTimer = GetTime() - lastUpdateTime;
			break;
		case KEY_DOWN: // Move block down 1 cell
			MoveBlockDown(true);
			downInputTimer = GetTime() - lastUpdateTime;
			break;

		case KEY_UP: // Rotate clockwise (right)
			RotateBlock(true);
			break;
		case KEY_Z: // Rotate counter-clockwise (left)
			RotateBlock(false);
			break;

		case KEY_SPACE: // Swap hold and current block
			HardDropBlock();
			break;

		case KEY_C: // Swap hold and current block
			HoldBlock();
			break;
	}

	// *** On Input Down (every frame the button is held)
	if (IsKeyDown(KEY_LEFT)) { // Left key down
		leftInputTimer += GetTime() - lastUpdateTime;
		while (leftInputTimer >= inputInterval + sideInputDelay) {
			MoveBlockLeft();
			leftInputTimer -= inputInterval;
		}
	}
	if (IsKeyDown(KEY_RIGHT)) { // Right key down
		rightInputTimer += GetTime() - lastUpdateTime;
		while (rightInputTimer >= inputInterval + sideInputDelay) {
			MoveBlockRight();
			rightInputTimer -= inputInterval;
		}
	}
	if (IsKeyDown(KEY_DOWN)) { // Down key down
		downInputTimer += GetTime() - lastUpdateTime;
		while (downInputTimer >= inputInterval) {
			MoveBlockDown(true);
			downInputTimer -= inputInterval;
		}
	}

	// Reset timers when key is not pressed
	if (leftInputTimer > 0 && IsKeyReleased(KEY_LEFT)) leftInputTimer = 0;
	if (rightInputTimer > 0 && IsKeyReleased(KEY_RIGHT)) rightInputTimer = 0;
	if (downInputTimer > 0 && IsKeyReleased(KEY_DOWN)) downInputTimer = 0;
}


// Moves the column of the current block 1 cell to the left
void Game::MoveBlockLeft()
{
	curBlock.Move(0, -1);

	// Wall collisions, undo block movement and don't count it as a lock move
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) {
		curBlock.Move(0, 1);
	}
	else { // If move allowed, have ghost block copy the movement
		ghostBlock.Move(0, -1);
		UpdateGhostBlockRow();
		if (numLockMoves < maxLockMoves) groundedTime = 0; // Only reset timer if block actually moved
		if (isBlockGrounded) numLockMoves++; // Count as locked move if grounded BEFORE the movement happens
	}
}

// Moves the column of the current block 1 cell to the right
void Game::MoveBlockRight()
{
	curBlock.Move(0, 1);

	// Wall collisions, undo block movement and don't count it as a lock movem
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) {
		curBlock.Move(0, -1);
	}
	else { // If move allowed, have ghost block copy the movement
		ghostBlock.Move(0, 1);
		UpdateGhostBlockRow();
		if (numLockMoves < maxLockMoves) groundedTime = 0; // Only reset timer if block actually moved
		if (isBlockGrounded) numLockMoves++; // Count as locked move if grounded BEFORE the movement happens
	}
}

// Moves the row of the current block 1 cell downwards and updates score for soft drops
void Game::MoveBlockDown(bool isSoftDrop)
{
	if (isBlockGrounded) {
		LockBlock(false); // Stop block from moving and spawn next block
	}
	else {
		curBlock.Move(1, 0);
		groundedTime = 0;
		if (isSoftDrop) UpdateScore(0, 1); // 1 point for pressing down key per grid space dropped
	}
}

// Moves the block to floor by repeatedly moving it down 1 cell for the number of rows in the grid
void Game::HardDropBlock()
{
	PlaySound(hardDropSfx);

	// Calculate points based on distance dropped
	int rowsDropped = ghostBlock.GetCellPositions()[0].row - curBlock.GetCellPositions()[0].row;
	if (rowsDropped > 0) {
		UpdateScore(0, rowsDropped * 2);
	}

	// Instantly snap current block to ghost block's position
	curBlock = ghostBlock;
	curBlock.isGhostBlock = false;

	// Immediately force lock the block in place
	UpdateIsBlockGrounded(); // Make sure isBlockGrounded is true before locking it
	LockBlock(true);
}

// Updates the game timer and lock timer, if the lock delay is reached the block is locked in grid
void Game::Update()
{
	UpdateIsBlockGrounded();
	HandleInput();

	if (gameOver) return;

	// Update Timer
	secondsElapsed += GetTime() - lastUpdateTime;
	if (secondsElapsed >= 60) {
		minutesElapsed++;
		secondsElapsed -= 60;
	}

	// Update time text with format mm::ss
	timeText.SetText((minutesElapsed < 10 ? "0" : "") + std::to_string(minutesElapsed) + ":" + (secondsElapsed < 10 ? "0" : "") + std::to_string((int)secondsElapsed));

	// Gravity Timer
	gravityTimer += GetTime() - lastUpdateTime;
	while (gravityTimer >= gravityInterval) { // While loop in case it misses a gravity interval due to low FPS
		gravityTimer -= gravityInterval;
		MoveBlockDown(false);
	}

	// Update lock timer
	if (isBlockGrounded) {
		groundedTime += GetTime() - lastUpdateTime;
		if (groundedTime >= lockDelay) LockBlock(true);
	}

	lastUpdateTime = GetTime();
}

// Returns true if any cells in current block is outside the boundaries of the game grid
bool Game::IsBlockOutside(Block block)
{
	std::vector<Position> filledCells = block.GetCellPositions();

	for (Position cell : filledCells) {
		if (grid.IsCellOutside(cell.row, cell.col)) return true;
	}
	return false;
}

// Rotates the block clockwise or counter clockwise and undoes the rotation if new block cell positions are outside the grid
void Game::RotateBlock(bool IsClockwise)
{
	if (isBlockGrounded && numLockMoves > maxLockMoves) LockBlock(true); // Prevent infinite rotations since block can become ungrounded after rotation

	curBlock.Rotate(IsClockwise);
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) {

		// *** Try to wall kick the block into a position that fits in the grid ***
		bool movedBlock = false;
		for (Position move : curBlock.GetRotationOffsetPositions()) {
			curBlock.Move(move.row, move.col);
			// If move doesn't fit, undo the move
			if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) curBlock.Move(-move.row, -move.col);
			// If move fits, have ghost block copy movement
			else {
				ghostBlock.Move(move.row, move.col);
				movedBlock = true;
				break;
			}
		}

		// Undo rotation and locked move if block cannot fit in grid after rotation
		if (movedBlock == false) {
			curBlock.Rotate(!IsClockwise);
			return;
		}
	}

	PlaySound(rotateSfx);
	ghostBlock.Rotate(IsClockwise);
	UpdateGhostBlockRow();
	if (numLockMoves < maxLockMoves) groundedTime = 0; // Only reset timer if block actually moved
	if (isBlockGrounded) numLockMoves++; // Count as locked move if grounded BEFORE the rotation happens
}

// Copies the current block cells onto the grid, spawns a new block, and clears any full rows
// Parameter forceLock is used to lock the block in place regardless of lock delay or max lock moves. Used for hard/soft drop.
void Game::LockBlock(bool forceLock)
{
	if (gameOver) return; // Prevent blocks from spawning after game over
	if (isBlockGrounded == false) return; // Don't lock block if it is not grounded

	// Don't count it as a lock if max lock moves and lock delay time has not been reached
	if (!forceLock && numLockMoves < maxLockMoves && groundedTime < lockDelay) return;

	// Copy block filled cell positions onto grid
	std::vector<Position> filledCells = curBlock.GetCellPositions();
	for (Position cell : filledCells) {
		grid.grid[cell.row][cell.col] = curBlock.id;
	}

	// Get new block and make sure it fits in grid when spawned
	SpawnNewBlock();
	if (BlockFits(curBlock) == false) { // Trigger Game Over
		gameOver = true;
		if (score > highScore) {
			highScore = score;
			highScoreText.SetText(std::to_string(highScore));
		}
	}

	int rowsCleared = grid.ClearFullRows();

	if (rowsCleared > 0) {
		PlaySound(clearSfx);
		UpdateScore(rowsCleared, 0);
		UpdateGhostBlockRow(); // Prevent bug where ghost block is floating since row was cleared AFTER ghost block was updated
		linesCleared += rowsCleared;
		linesText.SetText(std::to_string(linesCleared));

		// Trigger level up
		if (linesCleared >= curLevel * 10) {
			curLevel++;
			PlaySound(levelUpSfx);
			levelText.SetText(std::to_string(curLevel));
			gravityInterval = pow((0.8 - ((curLevel - 1) * 0.007)), curLevel - 1); // Gravity interval formula from NES Tetris))
		}
	}
	usedHold = false; // Allow player to hold block again
}

// Returns true if all cells in the current block are empty in the grid (it fits in current position on grid)
bool Game::BlockFits(Block block)
{
	std::vector<Position> filledCells = block.GetCellPositions();
	for (Position cell : filledCells) {
		if (!grid.IsCellEmpty(cell.row, cell.col)) return false;
	}
	return true;
}

// Wipes all blocks from grid, resets block pool, and spawns a new block
void Game::Reset()
{
	gameOver = false;
	grid.Initialize(); // Clear blocks on grid
	blocks = GetAllBlocks(); // Resets the pool of blocks to randomly choose from
	curBlock = GetRandomBlock();
	curBlock.MoveToStartPosition();
	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();
	nextBlock = GetRandomBlock();
	holdBlock.isHoldBlock = true;
	holdBlock.isHoldBlockSet = false;
	usedHold = false;

	// Locking
	numLockMoves = 0;
	groundedTime = 0;
	isBlockGrounded = false;

	// Stats
	linesCleared = 0;
	linesText.SetText(std::to_string(linesCleared));
	curLevel = 1;
	levelText.SetText(std::to_string(curLevel));
	score = 0;
	scoreText.SetText(std::to_string(score));

	// Timers
	minutesElapsed = 0;
	secondsElapsed = 0;
	gravityTimer = 0;
	gravityInterval = pow((0.8 - ((curLevel - 1) * 0.007)), curLevel - 1); // Gravity interval formula from NES Tetris))
	downInputTimer = 0;
	leftInputTimer = 0;
	rightInputTimer = 0;
	lastUpdateTime = GetTime();
}

// Updates the score variable depending on how many lines were cleared or how many times the block has been moved down
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared) {
		case 1:
			score += 100 * curLevel;
			break;
		case 2:
			score += 300 * curLevel;
			break;
		case 3:
			score += 500 * curLevel;
			break;
		case 4:
			score += 800 * curLevel;
			break;
		default:
			break;
	}

	score += moveDownPoints * curLevel;
	scoreText.SetText(std::to_string(score));
}

// Updates the row (or height) of the ghost block to accurately display the position of the current block if it were to move straight down
void Game::UpdateGhostBlockRow()
{
	// Move ghost block up until it reaches cur block (they are already have same rotation and column pos)
	while (ghostBlock.GetCellPositions()[0].row > curBlock.GetCellPositions()[0].row) { // Greater row number means lower in grid, (0,0) is top left
		ghostBlock.Move(-1, 0);
	}
	// Move ghost block down until it collides
	while (IsBlockOutside(ghostBlock) == false && BlockFits(ghostBlock)) {
		ghostBlock.Move(1, 0);
	}
	ghostBlock.Move(-1, 0);
}

// Swaps the current block with the hold block and updates the ghost and next block
void Game::HoldBlock()
{
	if (usedHold) return;
	usedHold = true;

	// If hold block is empty, put current block there and spawn new block
	if (holdBlock.isHoldBlockSet == false) {
		holdBlock.isHoldBlockSet = true;
		holdBlock = curBlock;
		holdBlock.Reset();
		SpawnNewBlock();
		return;
	}

	// Swap current and hold block
	Block tempHoldBlock = holdBlock;
	holdBlock = curBlock;
	curBlock = tempHoldBlock;
	curBlock.MoveToStartPosition();
	holdBlock.Reset();
	holdBlock.isHoldBlockSet = true;
	
	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();
}

// Spawns a new block and updates the ghost and next block
void Game::SpawnNewBlock()
{
	// Reset Variables for new block
	numLockMoves = 0;
	groundedTime = 0;
	isBlockGrounded = false;

	curBlock = nextBlock;
	curBlock.MoveToStartPosition();

	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();

	nextBlock = GetRandomBlock();
}

// Updates and returns isBlockGrounded variable to track is the current block is touching the floor or another block.
bool Game::UpdateIsBlockGrounded()
{
	curBlock.Move(1, 0);
	if (!IsBlockOutside(curBlock) && BlockFits(curBlock)) isBlockGrounded = false;
	else isBlockGrounded = true;
	curBlock.Move(-1, 0);
	return isBlockGrounded;
}
