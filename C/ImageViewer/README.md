# ImageViewer

An image viewer supporting JPG, PNG, TGA, BMP, PSD, GIF, HDR, and PIC formats using SDL2 and stb_image.

## How It Works

Loads images from the `Images/` folder using the single-header stb_image library, creates an SDL texture, and renders it in a window. Uses linear texture scaling for smooth display. Exit with ESC, Q, or close the window.

## Build

```bash
make
make run
```
