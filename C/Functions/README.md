# Mathematical Functions Visualizer

A C program that visualizes various mathematical functions using Raylib graphics library.

## Features
- Plot and visualize 8 different mathematical functions:
  - Sine (sin x)
  - Cosine (cos x)
  - Tangent (tan x)
  - Exponential (e^x)
  - Natural Logarithm (ln x)
  - Linear (x)
  - Quadratic (x²)
  - Absolute Value (|x|)
- Interactive menu to select which function to display
- Axes drawing with grid lines
- Real-time rendering at 60 FPS

## Requirements
- Raylib library
- Standard C libraries (math.h, stdio.h, etc.)

## Setup
1. Compile the program:
   ```bash
   gcc Functions.c -o Functions.exe -lraylib -lm
   ```

## Usage
```bash
./Functions.exe
```
Select a function from the menu (1-8) to visualize it in the graphics window.

## Controls
- Use the menu to select different functions
- Close the window or press ESC/Q to exit

## Notes
- The program uses a black background with red plots for visibility
- Axes are drawn with white lines and 50-unit grid spacing
- Each function is scaled appropriately for display within the 800x600 window