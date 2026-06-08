# Translator

Translates text between 30+ languages using the Google Translate free API endpoint.

## How It Works

Console app. User enters source language, target language, and text. The program constructs a Google Translate URL, fetches the result via libcurl, parses the response, and displays the translated text. Results are also saved to `Translation.txt`.

## Build

```bash
make
make run
```
