#pragma once

#include <raylib.h>
#include <vector>

// Extern = Global Variable. It lets us declare a variable in one file and use it in another
extern const Color darkGrey; // Empty cell
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

extern const Color lightBlue; // UI
extern const Color darkBlue; // UI

std::vector<Color> GetCellColors();