# Projects

> A collection of C, C++, and Python projects — games, tools, and utilities.

## Projects Overview

### C

| Project | Description |
|---------|-------------|
| [Weather](./C/Weather/) | Weather info for Algerian cities using OpenWeatherMap API |
| [TypeGame](./C/TypeGame/) | Typing speed game with difficulty levels |
| [Functions](./C/Functions/) | Mathematical function plotter (sin, cos, tan, etc.) |
| [ImageViewer](./C/ImageViewer/) | Image viewer supporting multiple formats via SDL2 |
| [MatchGame](./C/MatchGame/) | Match-3 puzzle game with Raylib |
| [QJG](./C/QJG/) | Quote and joke generator from public APIs |
| [QrCode](./C/QrCode/) | QR code generator outputting PNG |
| [SnakeGame](./C/SnakeGame/) | Classic snake game |
| [Sudoku](./C/Sudoku/) | Sudoku generator and solver |
| [TaskManager](./C/TaskManager/) | Graphical to-do list application |
| [Translator](./C/Translator/) | Translation using Google Translate API |
| [Interpreter](./C/Interpreter/) | Simple arithmetic expression interpreter |
| [Download_YT_Links](./C/Download_YT_Links/) | YouTube video/audio downloader |
| [OMORI](./C/OMORI/) | OMORI-inspired 2D exploration game |

### C++

| Project | Description |
|---------|-------------|
| [PING-PONG](./C++/PING-PONG/) | Pong game with AI opponent |
| [Game](./C++/Game/) | Space shooter with aliens and lasers |
| [Paint](./C++/Paint/) | Drawing application with brush tools |
| [Quiz](./C++/Quiz/) | Quiz game with heart character |
| [MPlayer](./C++/MPlayer/) | Music player with audio visualizer |
| [Pacman](./C++/Pacman/) | Classic Pac-Man game with C++20 and SFML |
| [Tetris](./C++/Tetris/) | Classic Tetris game with Raylib |

### Python

| Project | Description |
|---------|-------------|
| [DigitRecognition](./Python/DigitRecognition/) | CNN-based handwritten digit recognition |
| [AiChatBot](./Python/AiChatBot/) | CLI chatbot powered by Groq's Llama 3.3 API |

---

## Building

### C Projects

Each C project has a Makefile. Navigate to the project folder and run:

```bash
make        # Build
make run    # Build and run
make clean  # Remove executable
```

Works on Windows and Linux.

### C++ Projects

C++ projects use either a Makefile or CMake:

```bash
# Makefile projects
make && make run

# CMake projects (Pacman, Tetris)
mkdir -p build && cd build
cmake .. && cmake --build .
```

### Python Projects

Python projects use pip or uv for dependencies:

```bash
pip install -r requirements.txt
python main.py
```

---

## Directory Structure

```
Projects/
├── C/
│   ├── Weather/
│   ├── TypeGame/
│   ├── Functions/
│   ├── ImageViewer/
│   ├── MatchGame/
│   ├── QJG/
│   ├── QrCode/
│   ├── SnakeGame/
│   ├── Sudoku/
│   ├── TaskManager/
│   ├── Translator/
│   ├── Interpreter/
│   ├── Download_YT_Links/
│   └── OMORI/
├── C++/
│   ├── Game/
│   ├── MPlayer/
│   ├── Pacman/
│   ├── Paint/
│   ├── PING-PONG/
│   ├── Quiz/
│   └── Tetris/
└── Python/
    ├── DigitRecognition/
    └── AiChatBot/
```

---

## Libraries Used

| Library | Used By |
|---------|---------|
| **Raylib** | C games & graphics (Functions, MatchGame, SnakeGame, TaskManager, TypeGame, OMORI), C++ (Game, Quiz, Tetris) |
| **SDL2** | C++ PING-PONG, Paint; C ImageViewer |
| **SFML** | C++ MPlayer, Pacman |
| **libcurl** | C API clients (QJG, Translator, Weather) |
| **cJSON / json-c** | C JSON parsing (QJG, Weather) |
| **stb_image** | C ImageViewer image loading |
| **qrcodegen** | C QR code generation |
| **TensorFlow/Keras** | Python DigitRecognition CNN |
| **OpenCV** | Python DigitRecognition image preprocessing |
| **OpenAI SDK** | Python AiChatBot (Groq API) |
| **CS50 Library** | Various C projects (input helpers) |

---

## Notes

- **Weather** needs `OPENWEATHER_API_KEY` environment variable (or `.env` file)
- **Download_YT_Links** requires `yt-dlp` and `mpv` installed on your system
- **AiChatBot** needs a Groq API key in a `.env` file (`GROQ_API_KEY=...`)
- Some games need assets (fonts, images, sounds) in specific subdirectories — keep the folder structure intact
- **DigitRecognition** expects 28×28 grayscale images in `digits/` folder
- C projects use the CS50 library (`libcs50`) for simple user input
