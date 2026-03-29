# Weather Application

A C program that retrieves current weather information for Algerian cities using the OpenWeatherMap API.

## Features
- Fetches current weather data for Algerian cities
- Displays temperature, humidity, pressure, wind speed, cloudiness, and coordinates
- Validates input against a list of Algerian cities
- Shows weather description and additional details

## Requirements
- libcurl
- json-c library
- CS50 library (for get_string function)

## Setup
1. Create a `.env` file in the project root with your OpenWeatherMap API key:
   ```
   OPENWEATHER_API_KEY=your_api_key_here
   ```

2. Compile the program:
   ```bash
   ./run.sh
   ```
   or manually:
   ```bash
   gcc Weather.c -o Weather.exe -lcurl -ljson-c -lcs50
   ```

## Usage
```bash
./Weather.exe
```
Enter an Algerian city name when prompted to get the current weather information.

## Notes
- The API key is loaded from the `.env` file for security
- Only Algerian cities are supported (validation is performed)
- Temperature is displayed in Celsius