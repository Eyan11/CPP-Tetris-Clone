#include "grid.h"
#include <iostream>


// Constructor, initializes variables
Grid::Grid() 
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();
	colors = GetCellColors();
}

// Helper method to set all elements in grid 2d array to 0
void Grid::Initialize()
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			grid[row][col] = 0;
		}
	}
}

// Helper method to return a vector of all possible cell colors
std::vector<Color> Grid::GetCellColors()
{
	Color darkGrey = { 26, 31, 40, 255 }; // Empty cell
	Color green = { 47, 230, 23, 255 };
	Color red = { 232, 18, 18, 255 };
	Color orange = { 226, 116, 17, 255 };
	Color yellow = { 237, 234, 4, 255 };
	Color purple = { 166, 0, 247, 255 };
	Color cyan = { 21, 204, 209, 255 };
	Color blue = { 13, 64, 216, 255 };

	return { darkGrey , green, red, orange, yellow, purple, cyan, blue };
}

// Draws all grid colors with a margin to show grid outline
void Grid::Draw()
{
	int margin = 1;
	int cellValue = 0;
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			cellValue = grid[row][col];
			DrawRectangle(col * cellSize + margin, row * cellSize + margin,
				cellSize - margin, cellSize - margin, colors[cellValue]);
		}
	}
}



// Prints grid 2d array
void Grid::Print()
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			std::cout << grid[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
