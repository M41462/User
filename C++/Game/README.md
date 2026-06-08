# Game

A space shooter — control a spaceship, shoot lasers at descending aliens, and survive as long as possible.

## How It Works

Raylib renders a 700×650 game window. Move with arrow keys, shoot with Space (with cooldown). Aliens descend in waves — shooting one adds to your score. Collision with an alien ends the game. High score is persisted to `Score.txt`. Includes laser and explosion sound effects and a custom font.

## Build

```bash
cd src && make
make run
```
