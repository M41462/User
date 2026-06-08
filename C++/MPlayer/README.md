# MPlayer

A music player with an audio visualizer that browses and plays music from your `~/Music` directory.

## How It Works

Uses SFML for audio playback and graphics, and fzf for file selection. Supports MP4-to-WAV conversion via ffmpeg. Controls: Up/Down for volume, Left/Right for playback speed, M to mute, Space to play/pause, Q/Esc to quit. The visualizer renders real-time audio frequency bars.

## Build

```bash
cd src && make
make run
```

Requires SFML, fzf, and ffmpeg installed.
