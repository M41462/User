#include <cs50.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

struct LanguageMapping {
  const char *name;
  const char *code;
};
const struct LanguageMapping languages[] = {
    {"arabic", "ar"},   {"spanish", "es"},   {"french", "fr"},
    {"german", "de"},   {"italian", "it"},   {"portuguese", "pt"},
    {"russian", "ru"},  {"chinese", "zh"},   {"japanese", "ja"},
    {"korean", "ko"},   {"hindi", "hi"},     {"bengali", "bn"},
    {"punjabi", "pa"},  {"tamil", "ta"},     {"telugu", "te"},
    {"urdu", "ur"},     {"malayalam", "ml"}, {"kannada", "kn"},
    {"gujarati", "gu"}, {"oriya", "or"},     {"marathi", "mr"},
    {"bhojpuri", "bh"}, {"assamese", "as"},  {"avaric", "av"},
    {"bai", "ba"},      {"bengali", "bn"},   {"bihari", "bh"},
    {"bislama", "bi"},  {"burmese", "my"},   {"catalan", "ca"},
    {"chakma", "ccp"},  {"cherokee", "chr"}, {"chichewa", "ny"},
    {"chinese", "zh"},  {"cree", "cr"},      {"dari", "prs"},
    {"dutch", "nl"},    {"english", "en"},   {"esperanto", "eo"},
    {"estonian", "et"}, {"ewe", "ee"},       {"faroese", "fo"},
    {"fiji", "fj"},     {"finnish", "fi"},   {"french", "fr"},
    {"frisian", "fy"},  {"galician", "gl"},  {"georgian", "ka"},
    {"german", "de"},   {"gothic", "got"},
};

const size_t language_count = sizeof(languages) / sizeof(languages[0]);

const char *get_language_code(const char *code) {
  if (code == NULL) {
    return NULL;
  }
  if (strlen(code) == 2) {
    for (size_t i = 0; i < language_count; i++) {
      if (strcasecmp(code, languages[i].code) == 0) {
        return languages[i].code;
      }
    }
    return NULL;
  }

  for (size_t i = 0; i < language_count; i++) {
    if (strcasecmp(code, languages[i].name) == 0) {
      return languages[i].code;
    }
  }
  return NULL;
}

void print_supported_languages() {
  printf("Supported languages (name or code):\n");
  for (size_t i = 0; i < language_count; i++) {
    printf("- %s (%s)\n", languages[i].name, languages[i].code);
  }
}

void Init_Chunk(struct MemoryStruct *mem) {
  mem->memory = malloc(1);
  if (mem->memory == NULL) {
    fprintf(stderr, "Not enough memory (malloc returned NULL)\n");
    exit(EXIT_FAILURE);
  }
  mem->size = 0;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
  size_t new_size = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  char *ptr = realloc(mem->memory, mem->size + new_size + 1);
  if (ptr == NULL) {
    fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
    return 0;
  }
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, new_size);
  mem->size += new_size;
  mem->memory[mem->size] = '\0';
  return new_size;
}
char *url_encode(const char *str) {
  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    fprintf(stderr, "Curl Failed\n");
    return NULL;
  }
  char *output = curl_easy_escape(curl, str, 0);
  curl_easy_cleanup(curl);
  return output;
}

void Get_Output_File(const char *input_text, const char *translated_text) {
  FILE *fp = fopen("Translation.txt", "a");
  if (fp == NULL) {
    fprintf(stderr, "Failed to Read File");
    return;
  }
  fprintf(fp, "input text: %s\n", input_text);
  fprintf(fp, "output text: %s\n", translated_text);
  fclose(fp);
  return;
}

void Translate_Text(const char *text, const char *source, const char *output) {
  CURL *curl = curl_easy_init();
  CURLcode result;
  struct MemoryStruct chunk;
  Init_Chunk(&chunk);
  if (curl == NULL) {
    fprintf(stderr, "Curl Failed\n");
    goto cleanup;
  }
  char *encoded_text = url_encode(text);
  if (encoded_text == NULL) {
    fprintf(stderr, "Failed to encode text\n");
    goto cleanup;
  }
  char url[512];
  snprintf(url, sizeof(url),
           "https://translate.googleapis.com/translate_a/"
           "single?client=gtx&sl=%s&tl=%s&dt=t&q=%s",
           source, output, encoded_text);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
  result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
    fprintf(stderr, "Translation Failed\n");
    goto cleanup;
  } else {
    char *translated_text = strstr(chunk.memory, "\"");
    if (translated_text) {
      translated_text++;
      char *end_text = strchr(translated_text, '\"');
      if (end_text) {
        *end_text = '\0';
        printf("%s\n", translated_text);
        Get_Output_File(text, translated_text);
      }
    }
  }
cleanup: {
  free(chunk.memory);
  curl_free(encoded_text);
  curl_easy_cleanup(curl);
}
}

int main() {
  curl_global_init(CURL_GLOBAL_ALL);
  char *input_text = NULL;
  char *source_input = NULL;
  char *output_input = NULL;
  input_text = get_string("Enter Text to translate: ");
  if (input_text == NULL) {
    fprintf(stderr, "Failed to get input text\n");
    goto cleanup;
  }

  source_input = get_string("Enter Source Language: ");
  const char *source = get_language_code(source_input);
  if (source == NULL) {
    fprintf(stderr, "Unsupported source language: %s\n", source_input);
    print_supported_languages();
    goto cleanup;
  }

  output_input = get_string("Enter Output Language: ");
  const char *output = get_language_code(output_input);
  if (output == NULL) {
    fprintf(stderr, "Unsupported output language: %s\n", output_input);
    print_supported_languages();
    goto cleanup;
  }

  Translate_Text(input_text, source, output);

cleanup: {
  free(input_text);
  free(source_input);
  free(output_input);
  curl_global_cleanup();
}
  return EXIT_SUCCESS;
}
