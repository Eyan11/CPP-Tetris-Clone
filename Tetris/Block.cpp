#include <iostream>
#include "Block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffset = 0;
	colOffset = 0;
}

// Draws all filled cells with margin given its block id and rotation state
void Block::Draw()
{
	int margin = 1;
	std::vector<Position> filledCells = GetCellPositions(); // Get cells to draw using offset from movement

	for (Position cell : filledCells) {
		DrawRectangle(cell.col * cellSize + margin, cell.row * cellSize + margin,
			cellSize - margin, cellSize - margin, colors[id]);
	}
}

// Applies row/col offsets that are applied to block base position when drawn
void Block::Move(int rows, int cols)
{
	rowOffset += rows;
	colOffset += cols;
}

// Changes the rotation state of the block by incrementing or decrementing it while keeping it between 0 and 3
void Block::Rotate(bool isClockwise)
{
	// Cast cells size to int for O-block rotation to work
	if (isClockwise) {
		rotationState++;
		if (rotationState >= (int)cells.size()) rotationState = 0;
	}
	else {
		rotationState--;
		if (rotationState < 0) rotationState = (int)cells.size() - 1;
	}
}

// Returns world position of all cells by applying the row/col offsets to the filled cell positions
std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> filledCells = cells[rotationState];
	std::vector<Position> movedTiles;
	
	for (Position cell : filledCells) {
		Position newPos = Position(cell.row + rowOffset, cell.col + colOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}