#pragma once

#include <raylib.h>
#include <vector>

// Extern = Global Variable. It lets us declare a variable in one file and use it in another
extern const Color darkGrey; // Empty cell
extern const Color orange;
extern const Color blue;
extern const Color white;
extern const Color yellow;
extern const Color green;
extern const Color pink;
extern const Color red;

std::vector<Color> GetCellColors();