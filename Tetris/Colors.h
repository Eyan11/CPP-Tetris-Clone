#pragma once

#include <raylib.h>
#include <vector>

// Extern = Global Variable. It lets us declare a variable in one file and use it in another
extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

std::vector<Color> GetCellColors();