// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <raylib.h>
#include "Game.h"
#include "Colors.h"

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

    InitWindow(500, 620, "Tetris Clone");
    SetTargetFPS(60); // If no frame rate is defined it will run as fast as possible

    Font font = LoadFontEx("Assets/monogram.ttf", 64, 0, 0);

    Game game = Game();

    // Game Loop / Update
    while (WindowShouldClose() == false) // If escape or close icon pressed
    {
        // *** Game Loop Logic
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (OnIntervalTriggered(0.2)) game.MoveBlockDown(false, false);

        // *** Draw
        BeginDrawing();
        ClearBackground(backgroundColor); // Wipe previous frame's graphics and set all pixels to color

        // Score
        DrawTextEx(font, "Score", { 365,5 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,45,170,60 }, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score); // convert int to char array
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 55 }, 38, 2, WHITE);

        // Next Block
        DrawTextEx(font, "Next", { 370,115 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,155,170,180 }, 0.3, 6, lightBlue);

        // Hold Block
        DrawTextEx(font, "Hold", { 370,345 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,385,170,180 }, 0.3, 6, lightBlue);

        if(game.gameOver) DrawTextEx(font, "GAME OVER", { 320, 570 }, 38, 2, WHITE);

        game.Draw(); // Grid, curBlock, nextBlock, and holdBlock
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

