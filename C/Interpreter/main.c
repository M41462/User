#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1024

long eval_expr(const char *input, bool *ok) {
  char *ptr = (char *)input;
  char *end;

  long result = strtol(ptr, &end, 10);
  if (ptr == end) {
    *ok = false;
    return 0;
  }

  ptr = end;

  while (*ptr) {
    while (*ptr == ' ')
      ptr++;

    char op = *ptr;
    if (op != '+' && op != '-')
      break;
    ptr++;

    while (*ptr == ' ')
      ptr++;

    long value = strtol(ptr, &end, 10);
    if (ptr == end) {
      *ok = false;
      return 0;
    }

    if (op == '+')
      result += value;
    if (op == '-')
      result -= value;

    ptr = end;
  }

  *ok = true;
  return result;
}

int main(void) {
  printf("Simple Interpreter in C\n");

  char user_input[MAX_BUFFER];

  while (true) {
    printf("\n>>>>> ");
    fgets(user_input, MAX_BUFFER, stdin);
    user_input[strcspn(user_input, "\n")] = '\0';

    if (strcmp(user_input, "q") == 0 || strcmp(user_input, "Q") == 0)
      break;

    bool ok;
    long result = eval_expr(user_input, &ok);

    if (!ok) {
      printf("Invalid expression\n");
    } else {
      printf("= %ld\n", result);
    }
  }

  return EXIT_SUCCESS;
}
