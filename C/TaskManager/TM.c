#include <raylib.h>
#include <stdbool.h>
#include <string.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700
#define MAX_TASK_LEN 128
#define MAX_TASKS 12

typedef struct {
  char text[MAX_TASK_LEN];
  bool Done;
} TASK;

Vector2 Check_Rectangle = {.x = 90, .y = 180};
Vector2 Window_Reg = {.x = 50.f, .y = 25.f};
Vector2 offset = {.x = 150.f, .y = 150.f};

TASK tasks[MAX_TASKS];
int Task_Count = 0;

void Init_Window();
void Add_Task(Font font);
void Draw_Tasks(Font font);
void Remove_Task(int index);

int main() {
  Init_Window();
  return 0;
}

void Init_Window() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "To-Do List");
  SetTargetFPS(60);

  Font font = GetFontDefault();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleLines(Window_Reg.x, Window_Reg.y, SCREEN_WIDTH - 100,
                       SCREEN_HEIGHT - 50, WHITE);
    DrawRectangle(Window_Reg.x, Window_Reg.y, SCREEN_WIDTH - 100,
                  SCREEN_HEIGHT - 50, (Color){150, 150, 150, 255});

    DrawTextEx(font, "TODO LIST",
               (Vector2){Window_Reg.x + 10, Window_Reg.y + 10}, 32, 2, WHITE);

    Add_Task(font);
    Draw_Tasks(font);

    EndDrawing();
  }

  CloseWindow();
}

void Add_Task(Font font) {
  static char new_task_text[MAX_TASK_LEN] = {0};
  static int letters_count = 0;

  int key = GetCharPressed();
  while (key > 0) {
    if (letters_count < MAX_TASK_LEN - 1 && key >= 32 && key <= 125) {
      new_task_text[letters_count++] = (char)key;
      new_task_text[letters_count] = '\0';
    }
    key = GetCharPressed();
  }

  if (letters_count > 0 && IsKeyPressed(KEY_BACKSPACE)) {
    new_task_text[--letters_count] = '\0';
  }

  float boxX = offset.x - Window_Reg.x - 30;
  float boxY = offset.y - Window_Reg.y - 30;
  float boxW = SCREEN_WIDTH - 142;
  float boxH = 50;

  DrawRectangleLines(boxX, boxY, boxW, boxH, DARKGRAY);
  DrawTextEx(font, new_task_text, (Vector2){boxX + 10, boxY + 15}, 20, 1,
             DARKGREEN);
  if (IsKeyPressed(KEY_ENTER) && letters_count > 0 && Task_Count < MAX_TASKS) {
    strncpy(tasks[Task_Count].text, new_task_text, MAX_TASK_LEN);
    tasks[Task_Count].Done = false;
    Task_Count++;

    memset(new_task_text, 0, MAX_TASK_LEN);
    letters_count = 0;
  }
}

void Draw_Tasks(Font font) {
  for (int i = 0; i < Task_Count; i++) {
    int y = Check_Rectangle.y + i * 40;

    Rectangle checkbox = {Check_Rectangle.x, y, 20, 20};
    DrawRectangleLinesEx(checkbox, 2, DARKGRAY);

    if (tasks[i].Done) {
      DrawRectangleRec(checkbox, DARKGREEN);
    }

    DrawTextEx(font, tasks[i].text, (Vector2){checkbox.x + 30, y + 2}, 20, 1,
               BLACK);
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, checkbox)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        tasks[i].Done = !tasks[i].Done;
      }
      if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        Remove_Task(i);
      }
    }
  }
}

void Remove_Task(int index) {
  if (index < 0 || index >= Task_Count)
    return;
  for (int i = index; i < Task_Count - 1; i++) {
    tasks[i] = tasks[i + 1];
  }
  Task_Count--;
}
