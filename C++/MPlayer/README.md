A simple command-line music player with a graphical interface that allows you to:

Browse and select music files from your ~/Music directory

Play audio files (including converting MP4 to WAV)

Control playback with keyboard shortcuts

Features
File selection using fzf (fuzzy finder)

Volume control (increase/decrease/mute)

Playback speed adjustment

MP4 to WAV conversion

Keyboard-controlled interface

Dependencies
fzf (for file selection)

ffmpeg (for MP4 conversion)

SFML library (for audio playback and GUI)

Installation
Install dependencies:

bash
sudo apt install fzf ffmpeg libsfml-dev
Compile the program:

bash
g++ main.cpp UI.cpp MP.cpp -o music_player -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
Usage
Run the program:

bash
./music_player
Select a music file using the fuzzy finder interface

Use keyboard controls:

Up/Down: Volume control

Left/Right: Playback speed

M: Mute

Space: Play/Pause

Enter: Set volume to 70%

Q/Escape: Quit







