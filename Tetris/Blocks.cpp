#include "Block.h"
#include "Position.h"

/*
* Description: Defines all block types as children of the Block class
*/


class LBlock : public Block
{
public:
	LBlock() 
	{
		id = 1;
		cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
		cells[2] = { Position(2, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
		cells[3] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
        MoveToStartPosition();
    }
};


class JBlock : public Block // Reverse L
{
public:
    JBlock()
    {
        id = 2;
        cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) };
        cells[3] = { Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) };
        MoveToStartPosition();
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = 3;
        cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
        cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
        cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
        cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
        MoveToStartPosition();
    }
};

class OBlock : public Block // Square block, all rotations appear the same
{
public:
    OBlock()
    {
        id = 4;
        cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
        MoveToStartPosition();
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5;
        cells[0] = { Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) };
        cells[2] = { Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) };
        cells[3] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) };
        MoveToStartPosition();
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6;
        cells[0] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) };
        MoveToStartPosition();
    }
};

class ZBlock : public Block // Reverse S
{
public:
    ZBlock()
    {
        id = 7;
        cells[0] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) };
        cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) };
        MoveToStartPosition();
    }
};
