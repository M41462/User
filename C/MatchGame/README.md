# Match Game

A matching puzzle game where you align identical items to clear them from the board and score points.

## Features
- 10x10 game board with letter tiles (A-E)
- Match 2x2 blocks for 50 points
- Match 3-in-a-row horizontally or vertically for 30 points
- Penalty system: right-click to change a tile (loses 20 points or resets score to 0)
- Background music and sound effects
- Visual indicators for selected tiles
- Win condition: clear all tiles from the board

## Requirements
- Raylib library
- Standard C libraries (stdio.h, stdlib.h, time.h, stdbool.h)

## Setup
1. Ensure you have the required assets:
   - Music: `../Library/Music/assets_match.mp3`
   - Background: `../Library/Background/background.jpg`
2. Compile the program:
   ```bash
   gcc Match3.c -o match3.exe -lraylib
   ```

## Usage
```bash
./match3.exe
```
Game Controls:
- Left Click: Select a tile
- Arrow Keys: Move selected tile (when one is selected)
- Right Click: 
  - Without selection: Randomize the tile under cursor
  - With selection: Change the tile under cursor (incurs penalty)

## Objective
Clear all tiles from the board by creating matches. Try to achieve the highest score possible before running out of moves.

## Notes
- The game uses a fixed set of letters: A, B, C, D, E
- Tiles are randomized at the start and when changed via right-click
- Score is displayed in the top-left corner
- Win message appears when all tiles are cleared