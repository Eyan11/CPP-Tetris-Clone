#include <random>
#include "Game.h"

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	curBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
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
	switch (keyPressed) 
	{
		case KEY_LEFT: // Move block left 1 cell
			MoveBlockLeft();
			break;
		case KEY_RIGHT: // Move block right 1 cell
			MoveBlockRight();
			break;
		case KEY_DOWN: // Move block down 1 cell
			MoveBlockDown();
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
	curBlock.Move(0, -1);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) curBlock.Move(0, 1);
}

// Moves the column of the current block 1 cell to the right
void Game::MoveBlockRight()
{
	curBlock.Move(0, 1);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) curBlock.Move(0, -1);
}

// Moves the row of the current block 1 cell downwards
void Game::MoveBlockDown()
{
	curBlock.Move(1, 0);

	// Wall collisions, undo block movement
	if (IsBlockOutside() || !BlockFits()) {
		curBlock.Move(-1, 0);
		LockBlock(); // Stop block from moving and spawn next block
	}
}

// Moves the block to floor by repeatedly moving it down 1 cell for the number of rows in the grid
void Game::MoveBlockToFloor()
{
	for (int i = 0; i < grid.GetGridHeight() - 2; i++) MoveBlockDown();
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
	curBlock.Rotate(IsClockwise);
	if (IsBlockOutside() || !BlockFits()) curBlock.Rotate(!IsClockwise); // undo rotation if block is outside grid
	// TODO: instead of undoing the rotation, move block away from boundary
}

// Copies the current block cells onto the grid and spawns a new block
void Game::LockBlock()
{
	// Copy block filled cell positions onto grid
	std::vector<Position> filledCells = curBlock.GetCellPositions();
	for (Position cell : filledCells) {
		grid.grid[cell.row][cell.col] = curBlock.id;
	}

	// Spawn next block
	curBlock = nextBlock;
	nextBlock = GetRandomBlock();
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
