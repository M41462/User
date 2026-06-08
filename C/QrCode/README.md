# QrCode

Generates QR codes from user text input and saves them as PNG images.

## How It Works

Uses the qrcodegen library to encode user text into a QR code matrix (Medium error correction), then writes the result as a scaled PNG image using TinyPngOut. The user selects a mask pattern (0–7) and enters the text. Output saved to `output.png`.

## Build

```bash
make
make run
```
