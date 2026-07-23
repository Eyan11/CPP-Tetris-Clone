#pragma once

#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

class Block
{
public:
	Block();
	void Draw(float offsetX, float offsetY);
	void Move(int rows, int cols);
	void Rotate(bool isClockwise);
	std::vector<Position> GetCellPositions();
	void Reset();
	void MoveToStartPosition();
	std::vector<Position> GetRotationOffsetPositions();
	int id; // type of block, initialized in child class
	std::map<int, std::vector<Position>> cells; // map rotation state int to a vector filled cell indices (row, col)
	bool isGhostBlock;
	bool isHoldBlock;
	bool isHoldBlockSet; // False on game start, becomes true when user holds a block for the first time

protected:
	int rowOffset;
	int colOffset;

private:
	int cellSize;
	int rotationState; // 0-3 int for each block rotation (0, 90, 180, 270 degrees). Exception: O-block has only 1 rotation state
	std::vector<Color> colors; // all possible block colors
	std::vector<Position> rotationOffsetPositions; // Used for wall kick, stores the offset positions to try when rotating a block
	std::vector<Position> rotationOffsetPositionsIBlock; // For I-block wall kick, stores the offset positions to try when rotating a block
};