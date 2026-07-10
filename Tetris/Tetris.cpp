// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>

#include "grid.h"
#include "blocks.cpp" // Defines all block types

int main()
{
    Color backgroundColor = { 44, 44, 127, 255 };

    InitWindow(300, 600, "Tetris Clone");
    SetTargetFPS(60); // If no frame rate is defined it will run as fast as possible

    // Test grid
    Grid grid = Grid();
    grid.Print();

    JBlock block = JBlock();

    // Game Loop / Update
    while (WindowShouldClose() == false) // If escape or close icon pressed
    {
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color

        grid.Draw();
        block.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

