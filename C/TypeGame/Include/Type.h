#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROMPT_LENGTH 2048

extern const char *wordlist[100];
extern unsigned int wordlist_length;
extern char prompt[MAX_PROMPT_LENGTH];
const char *GetRandomWord();
void GenerateWordList(char *buffer, int count);

#endif
