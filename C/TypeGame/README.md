# TypeGame

A typing speed and accuracy game with three difficulty levels (Easy, Medium, Hard).

## How It Works

Raylib renders words on screen — type them correctly to advance. Real-time feedback shows green for correct letters, red for mistakes. Tracks accuracy (%), words per second, and wrong words. Stats are saved persistently to `UserData.txt`. Supports Ctrl+Backspace to delete 5 characters at once.

## Build

```bash
cd Src && make
make run
```
