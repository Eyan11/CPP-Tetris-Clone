# C++ Tetris

A classic Tetris clone built from scratch in **C++** using **Raylib**.

This project was created to strengthen my C++ game programming skills and gain experience building a complete game without relying on a game engine. The project includes piece movement and rotation, line clearing, scoring, level progression, T-spins, ghost pieces, hold functionality, and a 7-bag piece randomizer.

## Features

* Classic Tetris gameplay
* 10 × 20 playfield
* 7-bag random piece generation
* Seven standard Tetrominoes:

  * I
  * O
  * T
  * S
  * Z
  * J
  * L
* Piece movement and rotation
* Wall kicks
* Soft drop
* Hard drop
* Ghost piece
* Hold piece
* Next-piece preview
* Line clearing
* T-spins
* Level progression
* Increasing gravity speed
* Score tracking
* Game over detection

## Built With

* **C++**
* **Raylib**
* **Visual Studio 2022**
* **Git / GitHub**

## Technical Highlights

### Tetromino System

Each Tetromino is represented by a collection of blocks and supports rotation and movement while maintaining its current state.

The game separates the piece's logical position from the board, allowing pieces to be tested against the playfield before committing movement or rotation.

### Collision Detection

Before moving or rotating a piece, the game checks whether its resulting position would collide with:

* The boundaries of the playfield
* Existing placed blocks

This allows movement and rotation to be rejected when the resulting position would be invalid.

### Wall Kicks

The game implements wall-kick behavior to allow pieces to rotate when they are close to walls or other blocks.

This prevents rotations from feeling unnecessarily restrictive and matches modern Tetris gameplay.

### 7-Bag Randomizer

Instead of generating pieces completely randomly, the game uses a **7-bag randomizer**.

Each bag contains exactly one of every Tetromino. The pieces are shuffled and dealt to the player before generating another bag.

This prevents long streaks without receiving a particular piece and creates more consistent gameplay.

### Scoring System

The scoring system takes several factors into account, including:

* Lines cleared
* Level
* Hard drops
* Soft drops

## Controls

| Input           | Action                   |
| --------------- | ------------------------ |
| **Left Arrow**  | Move Left                |
| **Right Arrow** | Move Right               |
| **Down Arrow**  | Soft Drop                |
| **Space**       | Hard Drop                |
| **Up Arrow**    | Rotate                   |
| **z**           | Rotate Counter-Clockwise |
| **C**           | Hold Piece               |

## Level Progression

The game increases the falling speed of Tetrominoes as the player progresses through levels.

The gravity system is time-based, with the game moving a falling piece down one cell after a configurable amount of time has elapsed.

## Playing the Project

Download and play the project on Windows here: https://eyan11.itch.io/tetris 


## GIFS

<img width="800" height="712" alt="Tetris Opening" src="https://github.com/user-attachments/assets/d8199671-e8d4-4d37-924b-5e4aa4d474e4" />

<img width="800" height="712" alt="Tetris Clear" src="https://github.com/user-attachments/assets/addc53d9-7711-4218-bb59-531f1f1a57c3" />

<img width="800" height="712" alt="Tetris High Level" src="https://github.com/user-attachments/assets/5c990588-a372-421b-aeb6-def32fdf1b1d" />

## Credits

Built by **Eyan Martucci** as a C++ game programming project.

Tetris is a trademark of **The Tetris Company**. This project is an unofficial fan-made implementation created for educational and portfolio purposes.
