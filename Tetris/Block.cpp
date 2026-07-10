#include "Block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
}

// Draws all filled cells with margin given its block id and rotation state
void Block::Draw()
{
	int margin = 1;
	std::vector<Position> filledCells = cells[rotationState]; // Get cells to draw

	for (Position cell : filledCells) {
		DrawRectangle(cell.col * cellSize + margin, cell.row * cellSize + margin,
			cellSize - margin, cellSize - margin, colors[id]);
	}
}