# Interpreter

A simple arithmetic expression interpreter that evaluates `+`, `-`, `*`, `/` expressions left-to-right (no operator precedence).

## How It Works

REPL loop reads user input, removes whitespace, validates characters, then parses left-to-right: reads the first number, then iterates through operator–number pairs applying each operation to the running result. Handles division by zero. Type `exit` or `e` to quit.

## Build

```bash
make
make run
```
