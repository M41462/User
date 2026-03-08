#include "Type.h"
#include <stdio.h>

const char *wordlist[100] = {
    "the",  "of",    "and",    "to",    "in",    "is",    "you",    "that",
    "it",   "he",    "was",    "for",   "on",    "are",   "as",     "with",
    "his",  "they",  "I",      "at",    "be",    "this",  "have",   "from",
    "or",   "one",   "had",    "by",    "word",  "but",   "not",    "what",
    "all",  "were",  "we",     "when",  "your",  "can",   "said",   "there",
    "use",  "an",    "each",   "which", "she",   "do",    "how",    "their",
    "if",   "will",  "up",     "other", "about", "out",   "many",   "then",
    "them", "these", "so",     "some",  "her",   "would", "make",   "like",
    "him",  "into",  "time",   "has",   "look",  "two",   "more",   "write",
    "go",   "see",   "number", "no",    "way",   "could", "people", "my",
    "than", "first", "water",  "been",  "call",  "who",   "oil",    "its",
    "now",  "find",  "long",   "down",  "day",   "did",   "get",    "come",
    "made", "may",   "part",   "over"};

unsigned int wordlist_length = sizeof(wordlist) / sizeof(wordlist[0]);

char prompt[MAX_PROMPT_LENGTH] = {0};

const char *GetRandomWord() {
  int index = rand() % wordlist_length;
  return wordlist[index];
}

void GenerateWordList(char *buffer, int count) {
  printf("Generating %d words into buffer of size %d\n", count,
         MAX_PROMPT_LENGTH);

  if (buffer == NULL) {
    printf("ERROR: Buffer is NULL!\n");
    return;
  }

  buffer[0] = '\0';
  size_t current_length = 0;

  for (int i = 0; i < count; i++) {
    const char *word = GetRandomWord();
    size_t word_len = strlen(word);

    if (current_length + word_len + 2 > MAX_PROMPT_LENGTH) {
      printf("WARNING: Buffer full at word %d, stopping\n", i);
      break;
    }

    if (i > 0) {
      strcat(buffer, " ");
      current_length++;
    }

    strcat(buffer, word);
    current_length += word_len;

    printf("Added word %d: '%s' (total length: %zu)\n", i, word,
           current_length);
  }

  printf("Final prompt length: %zu, content: '%s'\n", strlen(buffer), buffer);
}
