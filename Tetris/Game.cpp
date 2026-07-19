#include <random>
#include <iostream>
#include "Game.h"

Game::Game() // Constructor
{
	grid = Grid();
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
	music = LoadMusicStream("Assets/Sounds/music.mp3");
	PlayMusicStream(music);
	rotateSfx = LoadSound("Assets/Sounds/rotate.mp3");
	clearSfx = LoadSound("Assets/Sounds/clear.mp3");
}

Game::~Game() // Destructor
{
	UnloadSound(rotateSfx);
	UnloadSound(clearSfx);
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
	curBlock.Draw(11, 11);

	if(!gameOver) ghostBlock.Draw(11, 11);

	switch (nextBlock.id) { // Make sure all block types are centered
		case 3: // I block
			nextBlock.Draw(255, 225);
			break;
		case 4: // O block
			nextBlock.Draw(255, 215);
			break;
		default:
			nextBlock.Draw(270, 205);
			break;
	}

	if (holdBlock.isHoldBlockSet) {
		switch (holdBlock.id) { // Make sure all block types are centered
			case 3: // I block
				holdBlock.Draw(345, 430);
				break;
			case 4: // O block
				holdBlock.Draw(375, 450);
				break;
			default:
				holdBlock.Draw(360, 440);
				break;
		}
	}
}

// Checks for input and calls respective method to handle it
void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) Reset(); // If game over and any key is pressed, restart

	if (gameOver) return; // Prevent input when game is over
		
	switch (keyPressed) 
	{
		case KEY_LEFT: // Move block left 1 cell
			MoveBlockLeft();
			break;
		case KEY_RIGHT: // Move block right 1 cell
			MoveBlockRight();
			break;
		case KEY_DOWN: // Move block down 1 cell
			MoveBlockDown(true, false);
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
}


// Moves the column of the current block 1 cell to the left
void Game::MoveBlockLeft()
{
	curBlock.Move(0, -1);

	// Wall collisions, undo block movement
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) curBlock.Move(0, 1);
	else { // If move allowed, have ghost block copy the movement
		ghostBlock.Move(0, -1);
		UpdateGhostBlockRow();
	}
}

// Moves the column of the current block 1 cell to the right
void Game::MoveBlockRight()
{
	curBlock.Move(0, 1);

	// Wall collisions, undo block movement
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) curBlock.Move(0, -1);
	else { // If move allowed, have ghost block copy the movement
		ghostBlock.Move(0, 1);
		UpdateGhostBlockRow();
	}
}

// Moves the row of the current block 1 cell downwards and returns true if move is allowed/successful
bool Game::MoveBlockDown(bool isSoftDrop, bool isHardDrop)
{
	curBlock.Move(1, 0);

	// Wall collisions, undo block movement
	if (IsBlockOutside(curBlock) || !BlockFits(curBlock)) {
		curBlock.Move(-1, 0);
		LockBlock(); // Stop block from moving and spawn next block
		return false;
	}

	if (isHardDrop) UpdateScore(0, 2); // 2 points for pressing up key per grid space dropped
	else if (isSoftDrop) UpdateScore(0, 1); // 1 point for pressing down key per grid space dropped
	return true;
}

// Moves the block to floor by repeatedly moving it down 1 cell for the number of rows in the grid
void Game::HardDropBlock()
{
	for (int i = 0; i < grid.GetGridHeight() - 2; i++) {
		if (MoveBlockDown(false, true) == false) break;
	}
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

		// Undo rotation if block cannot fit in grid after rotation
		if (movedBlock == false) {
			curBlock.Rotate(!IsClockwise);
			return;
		}
	}

	PlaySound(rotateSfx);
	ghostBlock.Rotate(IsClockwise);
	UpdateGhostBlockRow();
}

// Copies the current block cells onto the grid, spawns a new block, and clears any full rows
void Game::LockBlock()
{
	if (gameOver) return; // Prevent blocks from spawning after game over

	// Copy block filled cell positions onto grid
	std::vector<Position> filledCells = curBlock.GetCellPositions();
	for (Position cell : filledCells) {
		grid.grid[cell.row][cell.col] = curBlock.id;
	}

	// Get new block and make sure it fits in grid when spawned
	SpawnNewBlock();
	if (BlockFits(curBlock) == false) {
		gameOver = true;
	}

	int rowsCleared = grid.ClearFullRows();

	if (rowsCleared > 0) {
		PlaySound(clearSfx);
		UpdateScore(rowsCleared, 0);
		UpdateGhostBlockRow(); // Prevent bug where ghost block is floating since row was cleared AFTER ghost block was updated
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
	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();
	nextBlock = GetRandomBlock();
	holdBlock.isHoldBlock = true;
	holdBlock.isHoldBlockSet = false;
	usedHold = false;
	score = 0;
}

// Updates the score variable depending on how many lines were cleared or how many times the block has been moved down
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared) {
		case 1:
			score += 100;
			break;
		case 2:
			score += 300;
			break;
		case 3:
			score += 500;
			break;
		case 4:
			score += 800;
			break;
		default:
			break;
	}

	score += moveDownPoints;
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
	holdBlock.Reset();
	holdBlock.isHoldBlockSet = true;
	curBlock.MoveToStartPosition();
	
	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();
}

// Spawns a new block and updates the ghost and next block
void Game::SpawnNewBlock()
{
	curBlock = nextBlock;

	ghostBlock = curBlock;
	ghostBlock.isGhostBlock = true;
	UpdateGhostBlockRow();

	nextBlock = GetRandomBlock();
}