# Projects

C, C++, and Python projects - games, tools, and utilities.

## C Projects

| Project | Description |
|---------|-------------|
| [Weather](./C/Weather/) | Weather info for Algerian cities using OpenWeatherMap API |
| [TypeGame](./C/TypeGame/) | Typing speed game with difficulty levels |
| [Functions](./C/Functions/) | Mathematical function plotter (sin, cos, tan, etc.) |
| [ImageViewer](./C/ImageViewer/) | Image viewer supporting multiple formats |
| [MatchGame](./C/MatchGame/) | Match-3 puzzle game |
| [QJG](./C/QJG/) | Quote and joke generator from public APIs |
| [QrCode](./C/QrCode/) | QR code generator outputting PNG |
| [SnakeGame](./C/SnakeGame/) | Classic snake game |
| [Sudoku](./C/Sudoku/) | Sudoku generator and solver |
| [TaskManager](./C/TaskManager/) | To-do list application |
| [Translator](./C/Translator/) | Translation using Google Translate API |
| [Interpreter](./C/Interpreter/) | Simple arithmetic expression interpreter |
| [Download_YT_Links](./C/Download_YT_Links/) | YouTube video/audio downloader |

## C++ Projects

| Project | Description |
|---------|-------------|
| [PING-PONG](./C++/PING-PONG/) | Pong game with AI opponent |
| [Game](./C++/Game/) | Space shooter with aliens and lasers |
| [Paint](./C++/Paint/) | Drawing application with brush tools |
| [OMORI](./C++/OMORI/) | OMORI-inspired exploration game |
| [Quiz](./C++/Quiz/) | Quiz game with heart character |
| [MPlayer](./C++/MPlayer/) | Music player with visualizer |
| [Pacman](./C++/Pacman/) | Classic Pac-Man game with C++20 and SFML |

## Python Projects

| Project | Description |
|---------|-------------|
| [DigitRecognition](./Python/DigitRecognition/) | CNN-based handwritten digit recognition using TensorFlow/Keras |

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

# CMake projects (Pacman)
mkdir -p build && cd build
cmake .. && cmake --build .
```

### Python Projects
Python projects use pip for dependencies:

```bash
pip install -r requirements.txt
python main.py
```

## Structure

```
Projects/
├── C/
│   ├── Weather/
│   ├── TypeGame/
│   └── ...
├── C++/
│   ├── Game/
│   ├── PING-PONG/
│   ├── Pacman/
│   └── ...
└── Python/
    └── DigitRecognition/
```

## Libraries Used

- **Raylib** - C games and graphics
- **SDL2** - PING-PONG, Paint, ImageViewer
- **SFML** - MPlayer, Pacman
- **libcurl** - API requests
- **cJSON** - JSON parsing
- **TensorFlow/Keras** - DigitRecognition CNN
- **OpenCV** - DigitRecognition image preprocessing

## Notes

- Weather app needs `OPENWEATHER_API_KEY` env variable
- Download_YT_Links requires yt-dlp and mpv installed
- Some games need assets (fonts, images, sounds) in specific folders
- DigitRecognition expects 28×28 grayscale images in `digits/`