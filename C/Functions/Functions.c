#include <cs50.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 800
#define HEIGHT 600
typedef enum { SIN = 1, COS, TAN, EXP, LN, X, SQUARE, ABS } My_Functions;

void DrawAxes();
void Draw_Abs();
void Draw_Exp();
void Draw_Square();
void Draw_Sin();
void Draw_Tan();
void Draw_X();
void Draw_Cos();
void Draw_Ln();

int main(void) {
  Color BackGround = {0, 0, 0, 255};
  My_Functions function;
  do {
    printf("\n----Menu----\n");
    printf("1 - sin \n");
    printf("2 - cos \n");
    printf("3 - tan \n");
    printf("4 - e^x \n");
    printf("5 - ln \n");
    printf("6 - x \n");
    printf("7 - x^2 \n");
    printf("8 - |x|\n");

    function = get_int("Enter your integer value (1 - 8) : ");
  } while (function < 0 || function > 8);
  InitWindow(WIDTH, HEIGHT, "Functions");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BackGround);
    DrawAxes();
    switch (function) {

    case 1: {
      DrawText("Draw sin(x) ", 15, 15, 25, WHITE);
      Draw_Sin();
      break;
    }

    case 2: {
      DrawText("Draw cos(x) ", 15, 15, 25, WHITE);
      Draw_Cos();
      break;
    }
    case 3: {
      DrawText("Draw tan(x) ", 15, 15, 25, WHITE);
      Draw_Tan();
      break;
    }

    case 4: {
      DrawText("Draw e^x ", 15, 15, 25, WHITE);
      Draw_Exp();
      break;
    }

    case 5: {
      DrawText("Draw Ln ", 15, 15, 25, WHITE);
      Draw_Ln();
      break;
    }

    case 6: {
      DrawText("Draw x ", 15, 15, 25, WHITE);
      Draw_X();
      break;
    }
    case 7: {
      DrawText("Draw x^2 ", 15, 15, 25, WHITE);
      Draw_Square();
      break;
    }
    case 8: {
      DrawText("Draw | x | ", 15, GetScreenWidth() / 2 + 150, 25, WHITE);
      Draw_Abs();
      break;
    }
    default:
      continue;
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}

void DrawAxes(void) {
  DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, WHITE);
  DrawLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, WHITE);

  for (int i = -WIDTH / 2; i <= WIDTH / 2; i += 50) {
    DrawLine(WIDTH / 2 + i, HEIGHT / 2 - 5, WIDTH / 2 + i, HEIGHT / 2 + 5,
             WHITE);
  }

  for (int i = -HEIGHT / 2; i <= HEIGHT / 2; i += 50) {
    DrawLine(WIDTH / 2 - 5, HEIGHT / 2 + i, WIDTH / 2 + 5, HEIGHT / 2 + i,
             WHITE);
  }
}

void Draw_Square() {
  for (int x = -HEIGHT / 2; x < HEIGHT / 2; x++) {
    int y = x * x / 100;
    DrawPixel(x + WIDTH / 2, HEIGHT / 2 - y, RED);
  }
}

void Draw_Sin() {
  for (int px = 0; px < WIDTH; px++) {
    float x = (px - (float)WIDTH / 2) / 50.0f;
    float y = sinf(x);
    int py = HEIGHT / 2 - (int)(y * 100);
    DrawPixel(px, py, RED);
  }
}

void Draw_Cos() {
  for (int px = 0; px < WIDTH; px++) {
    float x = (px - (float)WIDTH / 2) / 50.0f;
    float y = cosf(x);
    int py = HEIGHT / 2 - (int)(y * 100);
    DrawPixel(px, py, RED);
  }
}

void Draw_Exp() {
  const float scaleX = 10.0f;
  const float scaleY = 20.0f;
  const int originX = WIDTH / 2;
  const int originY = HEIGHT / 2;

  for (int px = 0; px < WIDTH; px++) {
    float x = (px - originX) / scaleX;
    float y = expf(x);
    float py = originY - y * scaleY;

    if (py >= 0 && py < HEIGHT) {
      DrawPixel(px, (int)py, RED);
    }
  }
}

void Draw_Ln() {
  const float scaleX = 40.0f;
  const float scaleY = 20.0f;
  const int originX = WIDTH / 2;
  const int originY = HEIGHT / 2;

  float prevX = originX + 0.01f * scaleX;
  float prevY = originY - logf(0.01f) * scaleY;

  for (float x = 0.02f; x <= 10; x += 0.01f) {
    float y = logf(x);

    float sx = originX + x * scaleX;
    float sy = originY - y * scaleY;

    DrawLine((int)prevX, (int)prevY, (int)sx, (int)sy, RED);

    prevX = sx;
    prevY = sy;
  }
}

void Draw_Abs() {

  for (int x = -WIDTH / 2; x < WIDTH / 2; x++) {
    int y = abs(x);
    DrawPixel(x + WIDTH / 2, -y + HEIGHT / 2, RED);
  }
}

void Draw_Tan() {
  for (int px = 0; px < WIDTH; px++) {
    float x = (px - (float)WIDTH / 2) / 50.0f;
    float y = tanf(x);
    int py = HEIGHT / 2 - (int)(y * 100);
    DrawPixel(px, py, RED);
  }
}

void Draw_X() {
  for (int x = -WIDTH / 2; x < WIDTH / 2; x++) {
    int startX = WIDTH / 2 + x;
    int startY = HEIGHT / 2 - x;

    int endX = WIDTH / 2 + x + 1;
    int endY = HEIGHT / 2 - (x + 1);

    DrawLine(startX, startY, endX, endY, RED);
  }
}
