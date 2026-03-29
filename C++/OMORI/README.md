# OMORI Game

A game inspired by the OMORI RPG, developed using Raylib in C++.

## Features
- 2D game with character sprites and animations
- Collision detection system
- Interactive doors and objects
- Custom font rendering
- Sound effects and background music
- Game state management

## Requirements
- Raylib library
- Raymath library
- Rlgl library
- Standard C++ libraries

## Setup
1. Ensure you have Raylib development libraries installed
2. Place required assets in appropriate directories:
   - Fonts: `./Font/`
   - Images: `./Image/`
   - Sounds: `./Sound/`
3. Compile the program:
   ```bash
   gcc WS.c -o WS -lraylib -lraymath -lrlgl
   ```
   or use the provided run.sh script

## Usage
```bash
./WS
```
or
```bash
./run.sh
```

## Controls
- Typically involves arrow keys for movement
- Interaction keys for objects/doors
- Refer to in-game prompts or source code for specific controls

## Notes
- The game features a cat character and door objects as seen in the source code
- Animation system is implemented for smooth transitions
- Collision detection prevents movement through obstacles
- Assets should be placed in their respective directories for proper loading