# Tetris

The classic Tetris game built with C++17 and Raylib.

## How It Works

Seven tetromino pieces (I, O, T, S, Z, J, L) fall on a 10×20 board. Move with arrow keys, rotate with Up, hard drop with Space. Complete lines to clear them and score points. Features a next-piece preview, increasing speed over time, high score persistence, and background music. Three game states: Menu, Playing, Lose.

## Build

```bash
mkdir -p build && cd build
cmake .. && cmake --build .
```
