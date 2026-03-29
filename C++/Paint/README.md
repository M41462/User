# Paint

Simple paint application with SDL2.

## Features
- Smooth circle brush drawing
- Adjustable brush size
- 9 predefined colors
- Save drawings to PNG
- Clear canvas

## Requirements
- SDL2 library
- SDL2_image library

## Setup
```bash
cd Src
make
```

## Usage
```bash
./paint.exe  # Windows
./paint      # Linux
```

## Controls
- **Left Mouse Button**: Draw
- **Arrow Up**: Increase brush size
- **Arrow Down**: Decrease brush size
- **S**: Save to PNG (Saves folder)
- **Enter**: Clear canvas
- **ESC/Q**: Exit

## Notes
- Saves stored in `Saves/` folder
- Default brush radius is 8px
- Window size: 800x600