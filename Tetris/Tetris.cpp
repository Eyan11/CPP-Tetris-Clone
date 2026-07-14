// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>
#include "Game.h"

double lastUpdateTime = 0;

// Returns true if "interval" amount of time has passed
bool OnIntervalTriggered(double interval) 
{
    double curTime = GetTime();
    if (curTime - lastUpdateTime >= interval) {
        lastUpdateTime = curTime;
        return true;
    }
    return false;
}

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
        if (OnIntervalTriggered(0.2)) game.MoveBlockDown();

        // *** Draw
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color
        game.Draw(); // Handles drawing everything for the game
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

