# Pacman

A faithful recreation of the classic Pac-Man arcade game using C++20 and SFML.

## How It Works

Tile-based map with Pac-Man (arrow keys), four ghosts with distinct AI behaviors, pellets, power pellets, scoring, and lives. Ghosts scatter, chase, and flee when Pac-Man eats a power pellet. Includes a menu screen, sound effects, and a custom font. 896×1078 window at 60 FPS.

## Build

```bash
mkdir -p build && cd build
cmake .. && cmake --build .
```
