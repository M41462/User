# YouTube Media Downloader

A C program to download YouTube videos and audio in various formats (MP4, MP3, WAV) using yt-dlp and play them with mpv.

## Features
- Download YouTube videos as MP4
- Extract audio as MP3 or WAV
- Automatic dependency installation (yt-dlp and mpv)
- File naming to avoid overwrites
- Play downloaded media immediately after download
- Cross-platform support (Linux and Windows)

## Requirements
- yt-dlp
- mpv
- CS50 library (for get_string function)

## Setup
1. Install dependencies manually or let the program install them:
   - Linux: yt-dlp and mpv
   - Windows: yt-dlp and mpv via winget

2. Compile the program:
   ```bash
   gcc Download_YT_Links.c -o Download_YT_Links.exe -lcs50
   ```

## Usage
```bash
./Download_YT_Links.exe
```
Choose an option from the menu:
1. Download MP4 Video
2. Download MP3 Audio
3. Download WAV Audio
4. Exit

## Notes
- The program creates a "Music" directory to store downloaded files
- Files are named sequentially to avoid overwrites (video0.mp4, video1.mp4, etc.)
- After downloading, you can choose to play the file immediately