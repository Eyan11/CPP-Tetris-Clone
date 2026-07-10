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
	}
}


// Moves the column of the current block 1 cell to the left
void Game::MoveBlockLeft()
{
	curBlock.Move(0, -1);

	// Wall collisions, undo block movement
	if (IsBlockOutside()) curBlock.Move(0, 1);
}

// Moves the column of the current block 1 cell to the right
void Game::MoveBlockRight()
{
	curBlock.Move(0, 1);

	// Wall collisions, undo block movement
	if (IsBlockOutside()) curBlock.Move(0, -1);
}

// Moves the row of the current block 1 cell downwards
void Game::MoveBlockDown()
{
	curBlock.Move(1, 0);

	// Wall collisions, undo block movement
	if (IsBlockOutside()) curBlock.Move(-1, 0);
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