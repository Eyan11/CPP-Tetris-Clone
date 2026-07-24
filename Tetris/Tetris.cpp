// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>
#include "Game.h"
#include "Colors.h"

double lastUpdateTime = 0;
int windowWidth = 900;
int windowHeight = 800;
Color backgroundColor = { 44, 44, 127, 255 };

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
        if (OnIntervalTriggered(0.2)) game.MoveBlockDown(false, false);

        // *** Draw
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color
        game.Draw(); // Manager to draw everything
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
