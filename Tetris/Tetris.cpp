// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>
#include "Game.h"

int main()
{
    Color backgroundColor = { 44, 44, 127, 255 };

    InitWindow(300, 600, "Tetris Clone");
    SetTargetFPS(60); // If no frame rate is defined it will run as fast as possible

    Game game = Game();

    // Game Loop / Update
    while (WindowShouldClose() == false) // If escape or close icon pressed
    {
        // *** Game Loop Logic
        game.HandleInput();

        // *** Draw
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color
        game.Draw(); // Handles drawing everything for the game
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

