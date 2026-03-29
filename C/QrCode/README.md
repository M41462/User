# QR Code Generator

A C program that generates QR codes from text input and saves them as PNG images using the TinyPngOut library.

## Features
- Generate QR codes from user-provided text
- Customizable mask selection (0-7)
- High-quality PNG output using TinyPngOut
- Configurable scaling (default 10x)
- Error correction and validation

## Requirements
- qrcodegen library
- TinyPngOut library
- CS50 library (for get_string and get_int functions)
- Standard C libraries

## Setup
1. Ensure you have the required libraries installed:
   - qrcodegen
   - TinyPngOut
   - CS50

2. Compile the program:
   ```bash
   gcc main.c -o main.exe -lqrcodegen -ltinypngout -lcs50
   ```

## Usage
```bash
./main.exe
```
1. Enter the mask number (0-7) when prompted
2. Enter the text you want to encode in the QR code
3. The program will generate `output.png` in the current directory

## Notes
- The QR code is saved as `output.png` in the project directory
- Mask numbers affect the QR code pattern but not its readability
- The program uses MEDIUM error correction level
- Version ranges from MIN to MAX are automatically selected based on input size