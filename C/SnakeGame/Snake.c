#include <cs50.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#define WIDTH 800
#define HEIGHT 600
#define MAX_SPEED 50
#define Radius 8.52f
#define SNAKE_BODY 1000

typedef struct Reg {
  float posX;
  float posY;
  int REC_WIDTH;
  int REC_HIGHT;
} Reg;

int main() {
  InitAudioDevice();
  SetRandomSeed(time(NULL));

  Reg Snake;
  Snake.posX = 400;
  Snake.posY = 300;
  Snake.REC_WIDTH = 20;
  Snake.REC_HIGHT = 20;

  bool If_Continue = true;
  Vector2 Snake_Length[SNAKE_BODY];
  Snake_Length[0] = (Vector2){Snake.posX, Snake.posY};
  int body_length = 1;

  InitWindow(WIDTH, HEIGHT, "SNAKE GAME WINDOW");
  SetTargetFPS(60);

  int randomX = GetRandomValue(0, WIDTH - 50);
  int randomY = GetRandomValue(0, HEIGHT - 50);
  float score = 0;
  bool If_Lose = false;

  Vector2 Direction = {0, 0};
  Vector2 Snake_Speed = {0.81f, 0.81f};

  do {
    Rectangle snakehead = {Snake.posX, Snake.posY, Snake.REC_WIDTH,
                           Snake.REC_HIGHT};
    Vector2 Circle_Position = {randomX, randomY};

    ClearBackground(BLACK);
    DrawText(TextFormat("Score : %1.f", score), 0, 0, 25, WHITE);

    if (IsKeyPressed(KEY_DOWN) && Direction.y == 0) {
      Direction = (Vector2){0, 2.5};
    }
    if (IsKeyPressed(KEY_UP) && Direction.y == 0) {
      Direction = (Vector2){0, -2.5};
    }
    if (IsKeyPressed(KEY_LEFT) && Direction.x == 0) {
      Direction = (Vector2){-2.5, 0};
    }
    if (IsKeyPressed(KEY_RIGHT) && Direction.x == 0) {
      Direction = (Vector2){2.5, 0};
    }

    if (Snake.posX < 0 || Snake.posY < 0 ||
        Snake.posX > WIDTH - Snake.REC_WIDTH ||
        Snake.posY > HEIGHT - Snake.REC_HIGHT) {
      If_Lose = true;
    }

    Snake.posX += Direction.x * Snake_Speed.x;
    Snake.posY += Direction.y * Snake_Speed.y;

    for (int i = body_length - 1; i > 0; i--) {
      Snake_Length[i] = Snake_Length[i - 1];
    }
    Snake_Length[0] = (Vector2){Snake.posX, Snake.posY};

    if (CheckCollisionCircleRec(Circle_Position, Radius, snakehead)) {
      score += 50;
      body_length++;
      Snake_Speed.x = 0.82f + (score / 1000);
      Snake_Speed.y = 0.82f + (score / 1000);

      bool validPos = false;
      while (!validPos) {
        validPos = true;
        randomX = GetRandomValue(0, WIDTH - 50);
        randomY = GetRandomValue(0, HEIGHT - 50);

        for (int i = 0; i < body_length; i++) {
          if (CheckCollisionPointRec(
                  (Vector2){randomX, randomY},
                  (Rectangle){Snake_Length[i].x, Snake_Length[i].y,
                              Snake.REC_WIDTH, Snake.REC_HIGHT})) {
            validPos = false;
            break;
          }
        }
      }
    }

    for (int i = 0; i < body_length; i++) {
      DrawRectangle(Snake_Length[i].x, Snake_Length[i].y, Snake.REC_WIDTH,
                    Snake.REC_HIGHT, GREEN);
    }

    if (If_Lose) {
      DrawText("GAME OVER (PRESS ENTER TO CONTINUE)", 150, 100, 25, RED);

      if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        body_length = 1;
        Snake.posX = 400;
        Snake.posY = 300;
        score = 0;
        If_Lose = false;
        Snake_Speed = (Vector2){0.81f, 0.81f};
        Direction = (Vector2){0, 0};
      }

      if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q)) {
        If_Continue = false;
        break;
      }
    }

    DrawCircle(randomX, randomY, Radius, RED);
    EndDrawing();
  } while (!WindowShouldClose() && If_Continue);

  CloseAudioDevice();
  CloseWindow();
  return 0;
}
