# Sudoku

Generates random Sudoku puzzles and solves them using recursive backtracking.

## How It Works

Console menu-driven app. Generates a puzzle by placing 25 random valid numbers on a 9×9 board. The solver uses recursive backtracking — tries numbers 1–9 in each empty cell and backtracks when a conflict is found in the row, column, or 3×3 box. Tracks attempts and solving time.

## Build

```bash
make
make run
```
