# PING-PONG

A classic Pong game with an AI opponent, built with SDL2.

## How It Works

Player 1 controls the left paddle with W/S keys. The right paddle is AI-controlled and tracks the ball. Hit the ball past your opponent to score. First to reach the target score wins. Scores are persisted to `Data/data.txt`. Includes sound effects and a custom font.

## Build

```bash
cd main && make
make run
```
