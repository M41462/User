#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GRID 9
#define SUB_GRID 3
#define MAX_ATTEMPTS 1000

int Board[GRID][GRID];
int attempts = 0;

int Get_Random_Number(void) { return (rand() % GRID) + 1; }
void Init_Board(int Board[GRID][GRID]) {
  int i, j;
  for (i = 0; i < GRID; i++) {
    for (j = 0; j < GRID; j++) {
      Board[i][j] = 0;
    }
  }
}

bool Is_Boxes_Valid(int Board[GRID][GRID], int row, int col) {
  bool seen[10] = {false};
  for (int i = 0; i < SUB_GRID && row + i < GRID; i++) {
    for (int j = 0; j < SUB_GRID && col + j < GRID; j++) {
      int val = Board[row + i][col + j];
      if (val == 0)
        continue;
      if (seen[val])
        return false;
      seen[val] = true;
    }
  }
  return true;
}
bool Are_Boxes_Valid(int Board[GRID][GRID]) {
  for (int i = 0; i < GRID; i += SUB_GRID) {
    for (int j = 0; j < GRID; j += SUB_GRID) {
      if (!Is_Boxes_Valid(Board, i, j))
        return false;
    }
  }
  return true;
}

bool Is_Valid(int Board[GRID][GRID]) {
  for (int i = 0; i < GRID; i++) {
    bool seen[10] = {false};
    for (int j = 0; j < GRID; j++) {
      int val = Board[i][j];
      if (val == 0)
        continue;
      if (seen[val])
        return false;
      seen[val] = true;
    }
  }

  for (int j = 0; j < GRID; j++) {
    bool seen[10] = {false};
    for (int i = 0; i < GRID; i++) {
      int val = Board[i][j];
      if (val == 0)
        continue;
      if (seen[val])
        return false;
      seen[val] = true;
    }
  }

  if (!Are_Boxes_Valid(Board))
    return false;

  return true;
}
bool Is_Board_Full(int Board[GRID][GRID]) {
  for (int i = 0; i < GRID; i++) {
    for (int j = 0; j < GRID; j++) {
      if (Board[i][j] == 0)
        return false;
    }
  }
  return true;
}
bool Solve_Sudoku(int Board[GRID][GRID]) {
  if (!Is_Board_Full(Board)) {
    for (int i = 0; i < GRID; i++) {
      for (int j = 0; j < GRID; j++) {
        if (Board[i][j] == 0) {
          for (int num = 1; num <= GRID; num++) {
            Board[i][j] = num;
            if (Is_Valid(Board)) {
              if (Solve_Sudoku(Board)) {
                return true;
              }
            }
            Board[i][j] = 0;
          }
          return false;
        }
      }
    }
  }
  return true;
}
void Set_Board(int Board[GRID][GRID]) {
  Init_Board(Board);
  int count = 0;
  do {
    int row = rand() % GRID;
    int col = rand() % GRID;
    if (Board[row][col] == 0) {
      int num = Get_Random_Number();
      Board[row][col] = num;
      if (Is_Valid(Board)) {
        count++;
      } else {
        Board[row][col] = 0;
      }
    }
    attempts++;
  } while (count < 25 && attempts < MAX_ATTEMPTS);
}

void print_board(int Board[GRID][GRID]) {
  int i, j;
  for (i = 0; i < GRID; i++) {
    for (j = 0; j < GRID; j++) {
      printf("%d ", Board[i][j]);
    }
    printf("\n");
  }
}

void Menu() {
  do {
    printf("\n---MENU---\n");
    printf("1 - Init Sudoku Board\n");
    printf("2 - Solve Sudoku Board\n");
    printf("3 - Print Sudoku Board\n");
    printf("4 - EXIT \n");
    char Choice = get_char("Enter your Choice : ");
    switch (Choice) {
    case '1': {
      Set_Board(Board);
      break;
    }
    case '2': {
      if ((!Is_Valid(Board) || !Solve_Sudoku(Board)) && !Is_Board_Full(Board)) {
        printf("Invalid Board\n");
        continue;
      }
      Solve_Sudoku(Board);
      break;
    }
    case '3': {
      print_board(Board);
      break;
    }
    case '4': {
      goto exit;
      break;
    }
    default:
      continue;
    }
  } while (true);
exit:
  printf("Exiting...\n");
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  clock_t start = clock();
  Menu();
  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time Taken : %.2f Seconds\n", time_spent);
  printf("Attempts : %d\n", attempts);
  return EXIT_SUCCESS; 
}
