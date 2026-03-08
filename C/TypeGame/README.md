A simple yet challenging typing game built with Raylib and C to test and improve your typing speed and accuracy.

Features
Three Difficulty Levels: Easy, Medium, and Hard with varying word counts

Real-time Statistics: Tracks accuracy, words per second, and wrong words

Visual Feedback: Color-coded typing (green for correct, red for incorrect)

Line Wrapping: Text automatically wraps to fit screen width

Persistent Stats: Saves your performance data to a file

How to Play
Run the game and select your difficulty level

Type the displayed text as quickly and accurately as possible

Press Enter when finished or type until completion

View your stats (accuracy, speed, errors) after each session

Controls
Typing: Normal keyboard input

Backspace: Delete last character

Ctrl+Backspace: Delete last 5 characters

Enter: Submit/finish typing

Compilation & Running
bash
# Ensure you have Raylib installed
gcc -o TypeGame *.c -lraylib -lm
./TypeGame
File Structure
Init.c/h - Game initialization and main loop

Type.c/h - Word generation and text handling

User_Data.c/h - Statistics tracking and file I/O

UserData.txt - Saved performance data

Requirements
Raylib graphics library

C compiler (GCC, Clang, etc.)

Basic terminal/shell environment

License
Free to use and modify for educational purposes.
