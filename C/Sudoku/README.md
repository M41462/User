# Sudoku Generator and Solver

A C program that generates Sudoku puzzles and solves them using backtracking algorithm.

## Features
- Generate valid Sudoku boards with a configurable number of pre-filled cells
- Solve Sudoku puzzles using recursive backtracking
- Validate Sudoku board correctness (rows, columns, and 3x3 sub-grids)
- Check if board is completely filled
- Track generation attempts and solving time
- Interactive menu for different operations

## Requirements
- Standard C libraries (stdio.h, stdlib.h, time.h, unistd.h, stdbool.h)
- CS50 library (for get_char function)

## Setup
1. Compile the program:
   ```bash
   gcc Sudoku.c -o Sudoku.exe
   ```

## Usage
```bash
./Sudoku.exe
```
Menu Options:
1. Init Sudoku Board - Generate a new Sudoku puzzle
2. Solve Sudoku Board - Solve the current puzzle
3. Print Sudoku Board - Display the current board state
4. EXIT - Quit the program

## Algorithm Details
- Generation: Randomly places numbers and validates until reaching target count or max attempts
- Solving: Uses backtracking algorithm to try numbers 1-9 in empty cells
- Validation: Checks rows, columns, and 3x3 sub-grids for duplicates

## Notes
- Default target is 25 pre-filled cells for generated puzzles
- Maximum attempts set to 1000 for generation to prevent infinite loops
- Uses global 9x9 board array for simplicity
- Time and attempt counters are displayed upon exit