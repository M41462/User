# Translator

A translation tool that uses Google Translate API to translate text between languages.

## Features
- Translate text between 30+ languages
- Supports language name or code input
- Saves translations to file
- URL encoding for special characters

## Supported Languages
Arabic (ar), Spanish (es), French (fr), German (de), Italian (it), Portuguese (pt), Russian (ru), Chinese (zh), Japanese (ja), Korean (ko), Hindi (hi), Bengali (bn), Punjabi (pa), Tamil (ta), Telugu (te), Urdu (ur), Malayalam (ml), Kannada (kn), Gujarati (gu), Oriya (or), Marathi (mr), Assamese (as), Dutch (nl), English (en), Catalan (ca), Burmese (my), Estonian (et), Finnish (fi), Galician (gl), Georgian (ka)

## Requirements
- libcurl
- CS50 library

## Setup
```bash
make
```

## Usage
```bash
./Translator.exe  # Windows
./Translator      # Linux
```

Enter source language, target language, and text to translate.

## Notes
- Translations are saved to `Translation.txt`
- Uses Google Translate free API endpoint