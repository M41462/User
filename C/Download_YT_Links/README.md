# Download_YT_Links

Downloads YouTube videos and audio (MP4, MP3, WAV) using yt-dlp and plays them with mpv.

## How It Works

Menu-driven console app. Validates YouTube URLs, constructs yt-dlp commands, and executes them via the system shell. Downloaded files are saved to a `Music/` directory with unique sequential names. Optionally plays downloaded files with mpv.

## Build

```bash
make
make run
```

Requires `yt-dlp` and `mpv` installed on your system.
