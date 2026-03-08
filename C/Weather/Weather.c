#include <cs50.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <json-c/json.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define API_KEY "7ea5bdf50c6ad5e1ec8b9e949d393a41"
#define BASE_URL "https://api.openweathermap.org/data/2.5/weather"

struct string {
  char *buffer;
  size_t len;
};

FILE *fp;

void Init_string(struct string *s) {
  s->len = 0;
  s->buffer = malloc(1);
  if (s->buffer == NULL) {
    fprintf(stderr, "Failed Memory Allocation\n");
    exit(EXIT_FAILURE);
  }
  s->buffer[0] = '\0';
}

size_t Write_Callback(void *contents, size_t size, size_t nmemb, void *userp) {
  struct string *s = (struct string *)userp;

  size_t new_len = s->len + size * nmemb;
  char *tmp = realloc(s->buffer, new_len + 1);
  if (tmp == NULL) {
    fprintf(stderr, "Failed Memory Allocation\n");
    return 0;
  }

  s->buffer = tmp;
  memcpy(s->buffer + s->len, contents, size * nmemb);

  s->buffer[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

bool Is_Valid_Algerian_City(char *city_name) {
  const char *Algerian_Cities[58] = {"Adrar",         "Chlef",
                                     "Laghouat",      "Oum El Bouaghi",
                                     "Batna",         "Bejaia",
                                     "Biskra",        "Bechar",
                                     "Blida",         "Bouira",
                                     "Tamanrasset",   "Tebessa",
                                     "Tlemcen",       "Tiaret",
                                     "Tizi Ouzou",    "Algiers",
                                     "Djelfa",        "Jijel",
                                     "Setif",         "Saida",
                                     "Skikda",        "Sidi Bel Abbes",
                                     "Annaba",        "Guelma",
                                     "Constantine",   "Medea",
                                     "Mostaganem",    "Msila",
                                     "Mascara",       "Ouargla",
                                     "Oran",          "El Bayadh",
                                     "Illizi",        "Bordj Bou Arreridj",
                                     "Boumerdes",     "El Tarf",
                                     "Tindouf",       "Tissemsilt",
                                     "El Oued",       "Khenchela",
                                     "Souk Ahras",    "Tipaza",
                                     "Mila",          "Ain Defla",
                                     "Naama",         "Ain Temouchent",
                                     "Ghardaia",      "Relizane",
                                     "Timimoun",      "Bordj Badji Mokhtar",
                                     "Ouled Djellal", "Beni Abbes",
                                     "In Salah",      "In Guezzam",
                                     "Touggourt",     "Djanet",
                                     "El Mghair",     "El Meniaa"};

  int Countries = sizeof(Algerian_Cities) / sizeof(Algerian_Cities[0]);
  for (int i = 0; i < Countries; i++) {
    if (strcasecmp(city_name, Algerian_Cities[i]) == 0) {
      return true;
    }
  }
  return false;
}

void Get_Clear_Ouput(const char *json) {
  float temperature = 0;
  float humidity = 0.0f;
  float pressure = 0.0f;
  float wind_speed = 0.0f;
  float cloudiness = 0.0f;
  float latitude = 0.0f, longitude = 0.0f;
  char description[256];
  char city[256];
  char *temp_ptr = strstr(json, "\"temp\":");
  if (temp_ptr != NULL) {
    sscanf(temp_ptr, "\"temp\":%f", &temperature);
  }
  char *coord_ptr = strstr(json, "\"coord\"");
  if (coord_ptr != NULL) {
    char *lon_ptr = strstr(coord_ptr, "\"lon\":");
    char *lat_ptr = strstr(coord_ptr, "\"lat\":");

    if (lon_ptr != NULL) {
      sscanf(lon_ptr, "\"lon\":%f", &longitude);
    }
    if (lat_ptr != NULL) {
      sscanf(lat_ptr, "\"lat\":%f", &latitude);
    }
    char *hum_ptr = strstr(json, "\"humidity\":");
    if (hum_ptr != NULL) {
      sscanf(hum_ptr, "\"humidity\":%f", &humidity);
    }
    char *pres_ptr = strstr(json, "\"pressure\":");
    if (pres_ptr != NULL) {
      sscanf(pres_ptr, "\"pressure\":%f", &pressure);
    }
    char *wind_ptr = strstr(json, "\"speed\":");
    if (wind_ptr != NULL) {
      sscanf(wind_ptr, "\"speed\":%f", &wind_speed);
    }

    char *desc_ptr = strstr(json, "\"description\":\"");
    if (desc_ptr != NULL) {
      sscanf(desc_ptr, "\"description\":\"%[^\"]\"", description);
    }

    char *cloud_ptr = strstr(json, "\"all\":");
    if (cloud_ptr != NULL) {
      sscanf(cloud_ptr, "\"all\":%f", &cloudiness);
    }

    char *city_ptr = strstr(json, "\"name\":\"");
    if (city_ptr != NULL) {
      sscanf(city_ptr, "\"name\":\"%[^\"]\"", city);
    }
    printf("City : %s\n", city);
    printf("Temperature : %.2f°C\n", temperature);
    printf("Humidity : %.2f%%\n", humidity);
    printf("Pressure : %f\n", pressure);
    printf("Wind Speed : %f\n", wind_speed);
    printf("Coordinates: Latitude = %.2f, Longitude = %.2f\n", latitude,
           longitude);
    printf("Cloudiness : %f\n", cloudiness);
    printf("Description : %s\n", description);
  }
}
void Send_Request(char *city_name) {
  CURL *curl = curl_easy_init();
  struct string respond;
  if (curl == NULL) {
    printf("Failed Init Curl\n");
    exit(EXIT_FAILURE);
  }
  Init_string(&respond);
  char url[256];
  char *post_data = curl_easy_escape(curl, city_name, 0);
  snprintf(url, sizeof(url),
           "https://api.openweathermap.org/data/2.5/"
           "weather?q=%s,DZ&appid=%s&units=metric",
           post_data, API_KEY);
  curl_free(post_data);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Write_Callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&respond);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    fprintf(stderr, "Failed Curl\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Successfully sent request\n");
    Get_Clear_Ouput(respond.buffer);
  }
  free(respond.buffer);
  curl_easy_cleanup(curl);
}
int main(int argc, char *argv[]) {
  char *city_name;
  do {
    city_name = get_string("Enter the city name: ");
    system("clear");
    if (Is_Valid_Algerian_City(city_name)) {
      Send_Request(city_name);
    } else {
      printf("Invalid city name\n");
      return EXIT_FAILURE; // TODO: return error code
    }
  } while (Is_Valid_Algerian_City(city_name));
  return EXIT_SUCCESS;
}
