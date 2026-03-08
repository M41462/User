#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *QUOTE_URL = "https://api.quotable.io/random";
char *JOKE_URL = "https://official-joke-api.appspot.com/jokes/random";

struct Memory {
  char *URL;
  bool Is_URL_Joke;
  bool Is_URL_Quote;
  char *memory;
  size_t size;
};

static size_t Callback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t totalSize = size * nmemb;
  struct Memory *mem = (struct Memory *)userp;
  char *ptr = realloc(mem->memory, totalSize + mem->size + 1);
  if (ptr == NULL) {
    fprintf(stderr, "Not enough memory to allocate buffer.\n");
    return 0;
  }
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, totalSize);
  mem->size += totalSize;
  mem->memory[mem->size] = '\0';

  return totalSize;
}
char *Choice(struct Memory *mem) {
  char choice;
  do {
    printf("1. Quote\n2. Joke\n3. Exit\n");
    printf("Enter Choice : ");
    scanf(" %c", &choice);
    if (choice == '1') {
      mem->Is_URL_Joke = false;
      mem->Is_URL_Quote = true;
      return QUOTE_URL;
    } else if (choice == '2') {
      mem->Is_URL_Joke = true;
      mem->Is_URL_Quote = false;
      return JOKE_URL;
    }
  } while (choice != '3');
  printf("Exiting...\n");
  return NULL;
}

void Clear_Output(struct Memory *chunk) {
  cJSON *json = cJSON_Parse(chunk->memory);
  if (chunk->Is_URL_Quote) {
    if (json) {
      cJSON *content = cJSON_GetObjectItemCaseSensitive(json, "content");
      cJSON *author = cJSON_GetObjectItemCaseSensitive(json, "author");
      if (cJSON_IsString(content) && cJSON_IsString(author)) {
        printf("\"%s\"\n-\"%s\"\n", content->valuestring, author->valuestring);
      } else {
        printf("Could not parse quote.\n");
      }
      cJSON_Delete(json);
    } else {
      printf("Invalid JSON received. \n");
    }
  } else if (chunk->Is_URL_Joke) {
    if (json) {
      cJSON *joke = cJSON_GetObjectItemCaseSensitive(json, "setup");
      cJSON *punchline = cJSON_GetObjectItemCaseSensitive(json, "punchline");
      if (cJSON_IsString(joke) && cJSON_IsString(punchline)) {
        printf("\"%s\"\n\"%s\"\n", joke->valuestring, punchline->valuestring);
      } else {
        printf("Could not parse joke.\n");
      }
      cJSON_Delete(json);
    } else {
      printf("Invalid JSON received. \n");
    }
  }
}

int main(int argc, char *argv[]) {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL *curl = curl_easy_init();
  CURLcode result;
  struct Memory chunk;
  chunk.size = 0;
  chunk.memory = malloc(1);
  char *Ch = Choice(&chunk);
  if (chunk.memory == NULL) {
    fprintf(stderr, "Error Allocation Failed");
    free(chunk.memory);
    return EXIT_FAILURE;
  }
  if (curl != NULL && Ch != NULL) {
    curl_easy_setopt(curl, CURLOPT_URL, Ch);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    result = curl_easy_perform(curl);
    Clear_Output(&chunk);

    if (result != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(result));
      free(chunk.memory);
      return EXIT_FAILURE;
    }
    free(chunk.memory);
    curl_easy_cleanup(curl);
  }

  return EXIT_SUCCESS;
}
