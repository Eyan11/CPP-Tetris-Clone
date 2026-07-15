#include <random>
#include "Game.h"

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	curBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
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

// Handles calling all draw methods for the game (grid, block, etc.)
void Game::Draw()
{
	grid.Draw();
	curBlock.Draw();
}

// Checks for input and calls respective method to handle it
void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	// If game over and any key is pressed, restart
	if (gameOver && keyPressed != 0) Reset();
		
	switch (keyPressed) 
	{
		case KEY_LEFT: // Move block left 1 cell
			MoveBlockLeft();
			break;
		case KEY_RIGHT: // Move block right 1 cell
			MoveBlockRight();
			break;
		case KEY_DOWN: // Move block down 1 cell
			MoveBlockDown(true);
			break;
		case KEY_UP: // Move block to floor
			MoveBlockToFloor();
			break;

		case KEY_W: // Rotate clockwise
			RotateBlock(true);
			break;
		case KEY_D: // Rotate clockwise
			RotateBlock(true);
			break;

		case KEY_S: // Rotate counter-clockwise
			RotateBlock(false);
			break;
		case KEY_A: // Rotate counter-clockwise
			RotateBlock(false);
			break;
	}
}


// Moves the column of the current block 1 cell to the left
void Game::MoveBlockLeft()
{
	if (gameOver) return;

	curBlock.Move(0, -1);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) curBlock.Move(0, 1);
}

// Moves the column of the current block 1 cell to the right
void Game::MoveBlockRight()
{
	if (gameOver) return;

	curBlock.Move(0, 1);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) curBlock.Move(0, -1);
}

// Moves the row of the current block 1 cell downwards
void Game::MoveBlockDown(bool isSoftDrop, bool isHardDrop) // Both arguments are optional
{
	if (gameOver) return;

	curBlock.Move(1, 0);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) {
		curBlock.Move(-1, 0);
		LockBlock(); // Stop block from moving and spawn next block
	}
	else if (isHardDrop) UpdateScore(0, 2); // 2 points for pressing up key per grid space dropped
	else if (isSoftDrop) (UpdateScore(0, 1)); // 1 point for pressing down key per grid space dropped
}

// Moves the block to floor by repeatedly moving it down 1 cell for the number of rows in the grid
void Game::MoveBlockToFloor()
{
	if (gameOver) return;

	for (int i = 0; i < grid.GetGridHeight() - 2; i++) MoveBlockDown(false, true);
}

// Returns true if any cells in current block is outside the boundaries of the game grid
bool Game::IsBlockOutside()
{
	std::vector<Position> filledCells = curBlock.GetCellPositions();

	for (Position cell : filledCells) {
		if (grid.IsCellOutside(cell.row, cell.col)) return true;
	}
	return false;
}

// Rotates the block clockwise or counter clockwise and undoes the rotation if new block cell positions are outside the grid
void Game::RotateBlock(bool IsClockwise)
{
	if (gameOver) return;

	curBlock.Rotate(IsClockwise);
	if (IsBlockOutside() || !BlockFits()) curBlock.Rotate(!IsClockwise); // undo rotation if block is outside grid
	// TODO: instead of undoing the rotation, move block away from boundary
}

// Copies the current block cells onto the grid, spawns a new block, and clears any full rows
void Game::LockBlock()
{
	// Copy block filled cell positions onto grid
	std::vector<Position> filledCells = curBlock.GetCellPositions();
	for (Position cell : filledCells) {
		grid.grid[cell.row][cell.col] = curBlock.id;
	}

	// Get new block and make sure it fits in grid when spawned
	curBlock = nextBlock;
	if (BlockFits() == false) {
		gameOver = true;
	}

	// Spawn next block and clear any full rows
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared, 0);
}

// Returns true if all cells in the current block are empty in the grid (it fits in current position on grid)
bool Game::BlockFits()
{
	std::vector<Position> filledCells = curBlock.GetCellPositions();
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
	nextBlock = GetRandomBlock();
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
