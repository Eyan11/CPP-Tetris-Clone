#include <iostream>
#include "grid.h"
#include "Colors.h"


// Constructor, initializes variables
Grid::Grid() 
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialize();
	colors = GetCellColors(); // From Colors class
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

// Returns true if given cell position (row, col) is outside the boundaries of the game grid
bool Grid::IsCellOutside(int row, int col)
{
	return (row < 0 || row >= numRows || col < 0 || col >= numCols);
}

// Returns number of rows in the grid
int Grid::GetGridHeight()
{
	return numRows;
}

// Returns true if [row][cell] is empty in the grid
bool Grid::IsCellEmpty(int row, int col)
{
	return grid[row][col] == 0;
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
