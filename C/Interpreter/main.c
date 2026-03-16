#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1024

bool ValidInput(char *text, int size, int index) {
  if (size < 1 || !text)
    return false;
  char c = text[index];
  if (c == ' ')
    return false;
  bool hasDigits = isdigit((int)c);
  bool isOperator = (c == '+' || c == '-' || c == '*' || c == '/');
  return hasDigits || isOperator;
}

int output_result(char *text) {
  if (!text)
    return -1;

  int result = 0;

  int i = 0;
  while (isdigit(text[i])) {
    result = result * 10 + (int)(text[i] - '0');
    i++;
  }

  while (text[i] != '\0') {
    char operator = text[i];
    int number = 0;
    i++;
    while (isdigit(text[i])) {
      number = number * 10 + (int)(text[i] - '0');
      i++;
    }

    switch (operator) {
    case '+':
      result += number;
      break;
    case '-':
      result -= number;
      break;
    case '*':
      result *= number;
      break;
    case '/':
      if (number == 0) {
        fprintf(stderr, "Invalid Operation Devision by zero\n");
        return -1;
      }

      result /= number;
      break;
    default:
      printf("Invalid Operation\n");
      break;
    }
  }
  return result;
}

char *user_input_string(char *text) {
  int size = strlen(text);
  if (size < 1) {
    printf("Invalid input\n");
    return NULL;
  }
  char *result = malloc(size + 1);
  if (result == NULL) {
    printf("Memory Allocation Failed\n");
    return NULL;
  }
  int j = 0;
  for (int i = 0; i < size; i++) {
    char c = text[i];
    if (!ValidInput(text, size, i))
      continue;

    result[j++] = c;
  }
  result[j] = '\0';
  return result;
}

int main(int argc, char *argv[]) {

  char text[MAX_BUFFER];
  printf("Interpreter running ...\n");
  while (true) {
    printf(">>> ");
    fgets(text, MAX_BUFFER, stdin);
    bool exit = (strncmp(text, "exit", 4) == 0) || (strncmp(text, "e", 1) == 0);
    if (exit) {
      break;
    }
    char *input = user_input_string(text);
    int result = output_result(input);
    printf("input without spacing : %s\n", input);
    printf("result of the first number : %d\n", result);
    free(input);
  }

  return EXIT_SUCCESS;
}
