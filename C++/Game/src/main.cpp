
#include "./Game.hpp"
#include "common.hpp"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 700
#define HEIGHT 650
Sound Laser_Sound;
void Laser_Sound_Effect() { PlaySound(Laser_Sound); }

void Draw_Edges() {
  Rectangle rec = {0, 0, WIDTH, HEIGHT};
  DrawRectangleLinesEx(rec, 5, WHITE);
}

void Create_Window() {
  bool Is_Valid_Sound_Effect = true;
  InitWindow(WIDTH, HEIGHT, "SHOOTING GAME");
  InitAudioDevice();
  Game *game = new Game();

  if (game == NULL) {
    std::cerr << "Failed to create game instance" << std::endl;
    exit(EXIT_FAILURE);
  }

  Color Background = {29, 29, 27, 255};
  SetTargetFPS(60);

  Laser_Sound = LoadSound("../Sound/laser.ogg");

  if (!Valid_Sound(Laser_Sound)) {
    std::cerr << "Failed to load laser.ogg" << std::endl;
    Is_Valid_Sound_Effect = false;
    if (!Is_Valid_Sound_Effect) {
      exit(EXIT_FAILURE);
    }
  }
  float shootCoolDown = 0.3f;
  float shootTimer = 0.0f;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(Background);
    Draw_Edges();
    if (!game->GameOver()) {
      shootTimer -= GetFrameTime();
      if (shootTimer <= 0.0f && IsKeyPressed(KEY_SPACE)) {
        game->Shoot();
        Laser_Sound_Effect();
        shootTimer = shootCoolDown;
      }
      game->UpdateLaser();
      game->Movement();
      game->IsCollision();
    }
    game->Draw();
    EndDrawing();
  }
  game = NULL;
  delete game;
  UnloadSound(Laser_Sound);
  CloseAudioDevice();
  CloseWindow();
}

int main(void) {
  srand(time(NULL));
  Create_Window();
  return EXIT_SUCCESS;
}
