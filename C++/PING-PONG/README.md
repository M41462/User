# PING-PONG

Classic Pong game with AI opponent built using SDL2.

## Features
- Two-player mode (Player 1 vs AI)
- Score tracking
- Ball physics with increasing speed
- Sound effects
- Custom font rendering

## Requirements
- SDL2 library
- SDL2_image library
- SDL2_ttf library

## Setup
```bash
cd main
make
```

## Usage
```bash
./main.exe  # Windows
./main      # Linux
```

## Controls
- **W/S**: Move Player 1 paddle (left side)
- **SPACE/ENTER**: Start ball
- **ESC/Q**: Quit game

## Scoring
- Score increases when ball passes opponent's paddle
- Ball resets to center after each score
- Ball speed increases over time

## Notes
- Player 1 plays on the left side
- AI controls the right paddle
- Scores displayed at top of screen
- Sound plays on ball collision