# Image Viewer

A simple image viewer application using SDL2 and stb_image libraries.

## Features
- Load and display images from file
- Support for multiple image formats (JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC)
- Window icon support
- Smooth scaling with linear texture filtering
- Clean resource management

## Supported Formats
- JPG
- PNG
- TGA
- BMP
- PSD
- GIF
- HDR
- PIC

## Requirements
- SDL2 library
- SDL2_image library
- stb_image library (included as stb_image.h)

## Setup
1. Ensure you have SDL2 and SDL2_image development libraries installed
2. Compile the program:
   ```bash
   gcc main.c -o main.exe -lSDL2 -lSDL2_image
   ```

## Usage
```bash
./main.exe
```
The program will load and display `./Images/example0.png` by default.

## Controls
- ESC, RETURN, or Q: Exit the application
- Window close button: Exit the application

## Notes
- The image is loaded with RGBA conversion (4 channels)
- Texture scale mode is set to linear for smooth scaling
- Proper cleanup of all allocated resources on exit