#include "Colors.h"

const Color darkGrey = { 26, 31, 40, 255 }; // Empty cell

const Color orange = { 247, 158, 0, 255 };
const Color blue = { 40, 168, 247, 255 };
const Color white = { 255, 241, 232, 255 };
const Color yellow = { 247, 229, 38, 255 };
const Color green = { 0, 221, 52, 255 };
const Color pink = { 247, 115, 163, 255 };
const Color red = { 247, 0, 75, 255 };

std::vector<Color> GetCellColors()
{
	return { darkGrey, orange, blue, white, yellow, green, pink, red };
}