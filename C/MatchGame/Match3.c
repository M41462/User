#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define TILE_SIZE 42
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 700
const char random_letters[] = "ABCDE";
Vector2 offset = {
    ((float)SCREEN_HEIGHT / 2) - 175,
    ((float)SCREEN_WIDTH / 2) - 275,
};

bool If_Board_Empty(int Matrix[MAX][MAX]);
int Get_Random_Letter();
void Create_Window(int Matrix[MAX][MAX]);
void Print_Board(int Matrix[MAX][MAX]);
int main() {
  srand(time(NULL));
  int Matrix[MAX][MAX];
  Print_Board(Matrix);
  Create_Window(Matrix);
  return 0;
}

int Get_Random_Letter() {
  int Size = sizeof(random_letters) - 1;
  return rand() % Size;
}

void Print_Board(int Matrix[MAX][MAX]) {
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      Matrix[i][j] = random_letters[Get_Random_Letter()];
    }
  }
}

void Create_Window(int Matrix[MAX][MAX]) {
  int *Score = malloc(sizeof(int));
  if (!Score) {
    fprintf(stderr, "Failed Memory Allocation");
    return;
  }
  InitAudioDevice();
  Music music = LoadMusicStream("../Library/Music/assets_match.mp3");
  *Score = 0;
  bool Select_Block = false;
  bool Winner = false;
  Vector2 Mouse_Position = {0};
  Vector2 Selected_Tile = {-1, -1};
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MATCH2 GAME");
  SetTargetFPS(60);
  Texture2D background = LoadTexture("../Library/Background/background.jpg");
  while (!WindowShouldClose() && !Winner) {
    int grid_width = 10 * TILE_SIZE;
    int grid_height = 10 * TILE_SIZE;
    Vector2 grid_origin =
        (Vector2){((float)GetScreenWidth() - grid_width) / 2,
                  ((float)GetScreenHeight() - grid_height) / 2};
    Mouse_Position = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Select_Block = true;
      int x = (Mouse_Position.x - grid_origin.x) / TILE_SIZE;
      int y = (Mouse_Position.y - grid_origin.y) / TILE_SIZE;
      if (x >= 0 && x < MAX && y >= 0 && y < MAX) {
        Selected_Tile = (Vector2){x, y};
      }
    }
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && Select_Block) {
      int x = (Mouse_Position.x - offset.x) / TILE_SIZE;
      int y = (Mouse_Position.y - offset.y) / TILE_SIZE;

      if (x >= 0 && x < MAX && y >= 0 && y < MAX) {
        Matrix[x][y] = random_letters[Get_Random_Letter()];
      }
      if ((*Score) >= 20)
        *Score -= 20;
      else
        *Score = 0;
    }
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        Rectangle Rec = {
            i * TILE_SIZE + offset.x,
            j * TILE_SIZE + offset.y,
            TILE_SIZE,
            TILE_SIZE,
        };
        DrawRectangleLinesEx(Rec, 2, LIGHTGRAY);
        Vector2 Vect = {
            i * TILE_SIZE + offset.x + 15,
            j * TILE_SIZE + offset.y + 10,
        };

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !Select_Block) {
          Matrix[i][j] = random_letters[Get_Random_Letter()];
          *Score = 0;
        }

        if (i == Selected_Tile.x && j == Selected_Tile.y) {
          DrawRectangleLinesEx(
              (Rectangle){Selected_Tile.x * TILE_SIZE + offset.x,
                          Selected_Tile.y * TILE_SIZE + offset.y, TILE_SIZE,
                          TILE_SIZE},
              2, YELLOW);

          if (IsKeyPressed(KEY_LEFT) && i > 0) {
            char temp = Matrix[i][j];
            Matrix[i][j] = Matrix[i - 1][j];
            Matrix[i - 1][j] = temp;
          }

          if (IsKeyPressed(KEY_DOWN) && j < MAX - 1) {
            char temp = Matrix[i][j];
            Matrix[i][j] = Matrix[i][j + 1];
            Matrix[i][j + 1] = temp;
          }

          if (IsKeyPressed(KEY_RIGHT) && i < MAX - 1) {
            char temp = Matrix[i][j];
            Matrix[i][j] = Matrix[i + 1][j];
            Matrix[i + 1][j] = temp;
          }
          if (IsKeyPressed(KEY_UP) && j > 0) {
            char temp = Matrix[i][j];
            Matrix[i][j] = Matrix[i][j - 1];
            Matrix[i][j - 1] = temp;
          }

          if (i < MAX - 1 && j < MAX - 1 && Matrix[i][j] != ' ' &&
              Matrix[i][j] == Matrix[i + 1][j] &&
              Matrix[i][j] == Matrix[i][j + 1] &&
              Matrix[i][j] == Matrix[i + 1][j + 1]) {
            StopMusicStream(music);
            PlayMusicStream(music);
            UpdateMusicStream(music);
            *Score += 50;

            Matrix[i][j] = ' ';
            Matrix[i + 1][j] = ' ';
            Matrix[i][j + 1] = ' ';
            Matrix[i + 1][j + 1] = ' ';
          } else if (i < MAX - 2 && Matrix[i][j] != ' ' &&
                     Matrix[i][j] == Matrix[i + 1][j] &&
                     Matrix[i][j] == Matrix[i + 2][j]) {
            StopMusicStream(music);
            PlayMusicStream(music);
            UpdateMusicStream(music);
            (*Score) += 30;
            Matrix[i][j] = Matrix[i + 1][j] = Matrix[i + 2][j] = ' ';
          } else if (j < MAX - 2 && Matrix[i][j] != ' ' &&
                     Matrix[i][j] == Matrix[i][j + 1] &&
                     Matrix[i][j] == Matrix[i][j + 2]) {
            StopMusicStream(music);
            PlayMusicStream(music);
            UpdateMusicStream(music);
            (*Score) += 30;
            Matrix[i][j] = Matrix[i][j + 1] = Matrix[i][j + 2] = ' ';
          }
        }
        DrawTextEx(GetFontDefault(), TextFormat("%c", Matrix[i][j]), Vect, 20,
                   2.5, WHITE);
      }
    }
    Winner = If_Board_Empty(Matrix);
    if (Winner)
      DrawText("YOU WON!", 175, 15, 25, GREEN);
    DrawText(TextFormat("SCORE : %d", (*Score)), 15, 15, 25, YELLOW);
    EndDrawing();
  }
  WaitTime(2);
  UnloadMusicStream(music);
  UnloadTexture(background);
  CloseWindow();
  system("clear");
  if (Winner) {
    printf("You won the game \n");
    printf("Your score is %d \n", *Score);
  } else if (WindowShouldClose())
    printf("You Lost the Game\n");
  free(Score);
  return;
}

bool If_Board_Empty(int Matrix[MAX][MAX]) {
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      if (Matrix[i][j] != ' ') {
        return false;
      }
    }
  }
  return true;
}
