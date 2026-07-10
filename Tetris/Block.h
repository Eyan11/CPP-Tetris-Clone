#pragma once

#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

class Block
{
public:
	Block();
	void Draw();
	void Move(int rows, int cols);
	std::vector<Position> GetCellPositions();
	int id; // type of block, initialized in child class
	std::map<int, std::vector<Position>> cells; // map rotation state int to a vector filled cell indices (row, col)

private:
	int cellSize;
	int rotationState; // 0-3 int for each block rotation (0, 90, 180, 270)
	std::vector<Color> colors; // all possible block colors
	int rowOffset;
	int colOffset;
};