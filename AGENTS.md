# AGENTS.md

Personal multi-language monorepo (C, C++, Python). Independent projects, no cross-project dependencies.

## Build systems

- **C**: `clang` + Makefiles. Navigate to project dir, run `make` / `make run` / `make clean`. Flags: `-Wall -Wextra`.
- **C++**: Both Makefiles and CMake+vcpkg (manifest mode, `C++/vcpkg.json`). Equally valid. CMake builds go to `C++/build/bin/`. No CMake presets.
- **Python**: `AiChatBot/` uses `uv` (`uv sync` / `uv run main.py`). `DigitRecognition/` is plain `pip` (no `requirements.txt`, install manually: `tensorflow`, `opencv-python`, `numpy`, `matplotlib`).

## API keys & setup gotchas

- `C/Weather/` needs `OPENWEATHER_API_KEY` in `.env`
- `Python/AiChatBot/` needs `GROQ_API_KEY` in `.env` (rotate if exposed)
- `C/Download_YT_Links/` requires `yt-dlp` + `mpv` on PATH
- C projects expect CS50 library (`libcs50`) installed system-wide
- Assets (fonts, images, sounds) are bundled per-project — keep folder structure intact
- `Python/DigitRecognition/` expects 28×28 grayscale images in `digits/` folder

## What not to commit

- `.env` files (gitignored, but verify before `git add -A`)
- `vcpkg_installed/`, `build/`, `.vs/` (all gitignored)
- `*.o`, `*.h5`, `output.png`, `C++/Paint/Saves/` (all gitignored)

## No tests, no CI, no formatters

The only "lint" is `-Wall -Wextra` in Makefiles. No test framework exists — don't search for one.
