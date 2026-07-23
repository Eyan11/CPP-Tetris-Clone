#include <iostream>
#include "Block.h"

Block::Block()
{
	cellSize = 30;
	colors = GetCellColors();
	Reset();
	isGhostBlock = false;
	rotationOffsetPositions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
	rotationOffsetPositionsIBlock = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-2, 0}, {2, 0}, {0, -2}, {0, 2}, {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };
}

// Draws all filled cells with margin given its block id and rotation state
void Block::Draw(float offsetX, float offsetY)
{
	int cellMargin = 1;
	std::vector<Position> filledCells = GetCellPositions(); // Get cells to draw using offset from movement

	if (isGhostBlock == false) {
		for (Position cell : filledCells) {
			DrawRectangle(cell.col * cellSize + offsetX, cell.row * cellSize + offsetY,
				cellSize - cellMargin, cellSize - cellMargin, colors[id]);
		}
	}
	else { // Only draw cell outline for ghost blocks
		for (Position cell : filledCells) {
			DrawRectangleLines(cell.col * cellSize + offsetX, cell.row * cellSize + offsetY,
				cellSize - cellMargin, cellSize - cellMargin, colors[id]);
		}
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

// Resets row/col offset and rotation state to 0 (for hold block)
void Block::Reset()
{
	rowOffset = 0;
	colOffset = 0;
	rotationState = 0;
}

// Resets block and moves it to the start position in the middle top of the grid
void Block::MoveToStartPosition()
{
	Reset();

	switch (id) {
		case 3:
			Move(-1, 3);
			break;
		case 4:
			Move(0, 4);
			break;
		default:
			Move(0, 3);
			break;
	}
}

// Returns the wall kick offset positions for the block
std::vector<Position> Block::GetRotationOffsetPositions()
{
	if (id == 3) return rotationOffsetPositionsIBlock;
	else if (id != 4) return rotationOffsetPositions; // O-block has no wall kick offsets
	return { {0, 0} };
}
