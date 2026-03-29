# Simple Expression Interpreter

A C program that interprets and evaluates simple arithmetic expressions.

## Features
- Parses basic arithmetic expressions (addition, subtraction, multiplication, division)
- Removes whitespace from input for cleaner processing
- Evaluates expressions left-to-right (no operator precedence)
- Handles division by zero error detection
- Continuous operation until user types "exit" or "e"

## Requirements
- Standard C libraries (stdio.h, stdlib.h, string.h, ctype.h, math.h)

## Setup
1. Compile the program:
   ```bash
   gcc main.c -o interpreter.exe -lm
   ```

## Usage
```bash
./interpreter.exe
```
Enter arithmetic expressions like:
- "5+3"
- "10-4*2"
- "20/5+3"

Type "exit" or "e" to quit the program.

## Notes
- Expressions are evaluated strictly left-to-right (no operator precedence)
- Only single-digit operators are supported (+, -, *, /)
- Spaces in input are automatically removed
- Division by zero returns an error and continues the program