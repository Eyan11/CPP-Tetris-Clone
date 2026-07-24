// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>
#include "Game.h"
#include "Colors.h"

int windowWidth = 900;
int windowHeight = 800;
Color backgroundColor = { 44, 44, 127, 255 };

int main()
{
    InitWindow(windowWidth, windowHeight, "Tetris");
    SetTargetFPS(60); // If no frame rate is defined it will run as fast as possible

    Game game = Game(windowWidth, windowHeight);

    // Game Loop / Update
    while (WindowShouldClose() == false) // If escape or close icon pressed
    {
        // *** Game Loop Logic
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();

        // *** Draw
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color
        game.Draw(); // Manager to draw everything
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
