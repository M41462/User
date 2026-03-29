# Snake Game

A classic Snake game implementation using Raylib where the player controls a snake to eat food and grow longer.

## Features
- Classic snake gameplay with growing body
- Food spawns at random locations (avoiding snake body)
- Speed increases as score increases
- Game over conditions: hitting walls or self-collision
- Restart functionality after game over
- Score tracking and display
- Background music and sound effects

## Requirements
- Raylib library
- Standard C libraries (stdio.h, stdlib.h, time.h, unistd.h, stdbool.h, stdint.h)

## Setup
1. Ensure you have Raylib development libraries installed
2. Compile the program:
   ```bash
   gcc Snake.c -o Snake.exe -lraylib
   ```

## Usage
```bash
./Snake.exe
```
Game Controls:
- Arrow Keys: Change snake direction (Up, Down, Left, Right)
- ENTER or SPACE: Restart after game over
- ESC or Q: Quit the game

## Objective
Eat as much food as possible to grow your snake and achieve the highest score without crashing into walls or yourself.

## Notes
- Snake starts at position (400, 300) in an 800x600 window
- Initial speed is 0.81f, increases with score
- Food is represented as a red circle, snake body as green rectangles
- When game over, press ENTER or SPACE to restart or ESC/Q to quit