# Task Manager

A simple to-do list application built with Raylib.

## Features
- Add new tasks
- Mark tasks as done (left-click on checkbox)
- Remove tasks (right-click on checkbox)
- Visual checkbox indicators
- Maximum of 12 tasks

## Requirements
- Raylib library
- Standard C libraries

## Setup
```bash
make
```

## Usage
```bash
./TM.exe  # Windows
./TM      # Linux
```

## Controls
- **Type**: Enter task text
- **Enter**: Add task to list
- **Backspace**: Delete last character
- **Left Click (on checkbox)**: Toggle task completion
- **Right Click (on checkbox)**: Remove task

## Notes
- Tasks are stored in memory only (not persistent)
- Maximum task limit is 12 items
- Done tasks show as filled checkboxes