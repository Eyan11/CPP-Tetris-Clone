#pragma once

#include <vector>
#include <raylib.h>

class Grid {
public:
	Grid();
	void Initialize();
	void CenterGridInWindow(int windowWidth, int windowHeight);
	void Draw();
	bool IsCellOutside(int row, int col);
	int GetGridHeight();
	bool IsCellEmpty(int row, int col);
	int ClearFullRows();
	float GetGridCoordinateX(bool isLeftEdge);
	float GetGridCoordinateY(bool isTopEdge);
	int grid[20][10];

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	std::vector<Color> colors; // All possible cell colors
	int numRows;
	int numCols;
	int cellSize; // Pixel size of a cell
	Vector2 gridAnchorPos; // The position of the grid's anchor point (top left corner)
	int cellMargin; // The margin between cells to show grid lines
};