# Weather

Fetches current weather data for all 58 Algerian wilayas (provinces) using the OpenWeatherMap API.

## How It Works

Reads an API key from a `.env` file, prompts the user for an Algerian city name, validates it against a built-in list of all 58 provinces, then calls the OpenWeatherMap API via libcurl. The JSON response is parsed with json-c and displays temperature (°C), humidity, pressure, wind speed, cloudiness, and coordinates.

## Build

```bash
make
make run
```

Requires `OPENWEATHER_API_KEY` in a `.env` file or as an environment variable.
