#pragma once

#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void Move(int rows, int cols);
	void Rotate(bool isClockwise);
	std::vector<Position> GetCellPositions();
	int id; // type of block, initialized in child class
	std::map<int, std::vector<Position>> cells; // map rotation state int to a vector filled cell indices (row, col)
	bool isGhostBlock;

private:
	int cellSize;
	int rotationState; // 0-3 int for each block rotation (0, 90, 180, 270 degrees). Exception: O-block has only 1 rotation state
	std::vector<Color> colors; // all possible block colors
	int rowOffset;
	int colOffset;
};