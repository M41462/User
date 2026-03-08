#include "User_Data.h"

bool file_exist = false;
const char *filepath = "../Include/UserData.txt";

void Init_File(FILE *filepointer) {
  filepointer = fopen(filepath, "w+");
  if (filepointer == NULL) {
    perror("Error Creating File\n");
  }
  file_exist = true;
}
void Read_File(FILE *filepointer) {
  char buffer[MAX];
  filepointer = fopen(filepath, "r+");
  if (file_exist) {
    while (fgets(buffer, sizeof(buffer), filepointer)) {
      printf("%s", buffer);
    }
  }
  fclose(filepointer);
}

void Write_File(FILE *filepointer, float accuracy, double wps,
                int wrong_words) {
  filepointer = fopen(filepath, "a+");
  if (file_exist) {
    fprintf(filepointer,
            "Accuracy : %.2f\nWordPerSecond: : %.2f\nWrongWords: %d\n",
            accuracy, wps, wrong_words);
    fclose(filepointer);
  }
}

float Word_Per_Second(int words, int seconds) {
  return ((float)words / seconds) * 10;
}

float Accuracy(const char *Text, char *Input) {
  int text_length = strlen(Text);
  int input_length = strlen(Input);
  int Correct_Words = 0;
  for (int i = 0; i < text_length; i++) {
    if (Input[i] == Text[i])
      Correct_Words++;
  }
  return (Correct_Words / (float)input_length) * 100;
}
