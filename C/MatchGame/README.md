# MatchGame

A Match-3 puzzle game on a 10×10 grid. Match tiles (A–E) in 2×2 blocks or 3-in-a-row to clear them and score points.

## How It Works

Raylib renders a grid of random letter tiles. Click to select, use arrow keys to move the selection, and right-click to randomize (costs 20 points). Matching logic checks rows, columns, and 2×2 blocks. Clear all tiles to win. Includes background music and a background image.

## Build

```bash
make
make run
```
