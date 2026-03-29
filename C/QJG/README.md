# QJG - Quote and Joke Generator

Fetches random quotes and jokes from public APIs.

## Features
- Random quotes from quotable.io API
- Random jokes from official-joke-api.appspot.com
- Interactive menu system
- JSON parsing with cJSON

## Requirements
- libcurl
- cJSON library

## Setup
```bash
make
```

## Usage
```bash
./QJG.exe  # Windows
./QJG      # Linux
```

Choose from menu:
1. Get a random quote
2. Get a random joke
3. Exit

## Notes
- No API key required
- Uses free public APIs
- Clean JSON parsing and display