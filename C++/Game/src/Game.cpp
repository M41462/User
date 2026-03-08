#include "./Game.hpp"
#include <unistd.h>
#include "./alien.hpp"
#include <iostream>
#include "Space.hpp"
#include "common.hpp"

Sound Alien_Destroyed;
bool Is_Destroyed = false;
Game::~Game() {
  Destroy();
  alien.Destroy_Alien();
  UnloadFont(font);
  spaceShip.~SpaceShip();
  UnloadSound(Alien_Destroyed);
}

bool Valid_Font(Font font) {
  if (font.texture.id == 0) {
    return false;
  }
  return true;
}

bool Game::GameOver() {
  return alien.All_Alien_Destroyed() || spaceShip.Lives <= 0;
}
Game::Game() {
  alien.Init_Alien();
  alien.Init_Alien_Laser();
  Alien_Destroyed = LoadSound("../Sound/explosion.ogg");
  if (!Valid_Sound(Alien_Destroyed)) {
    std::cerr << "Failed to load explosion.ogg" << std::endl;
  }
}
void Game::IsCollision() {
  spaceShip.IsCollision();
  if (alien.IsAlienShotes(spaceShip.laser)) {
    spaceShip.laser.Active = false;
    Is_Destroyed = true;
    if (Is_Destroyed) {
      PlaySound(Alien_Destroyed);
    }
    Score += 10;
  }

  if (IsSpaceShipHitByAlienLaser()) {
    PlaySound(Alien_Destroyed);
    spaceShip.Lives--;
    spaceShip.laser.Active = false;
  }
}
bool Game::IsSpaceShipHitByAlienLaser() {
  Rectangle shipRect = {spaceShip.position.x, spaceShip.position.y,
                        (float)spaceShip.image.width,
                        (float)spaceShip.image.height};
  for (int i = 0; i < 14; i++) {
    if (alien.alien_laser[i].Active) {
      Rectangle laserRect = {alien.alien_laser[i].position.x,
                             alien.alien_laser[i].position.y, 3,
                             15}; 
      if (CheckCollisionRecs(shipRect, laserRect)) {
        alien.alien_laser[i].Active = false;
        return true;
      }
    }
  }
  return false;
}

void Game::Shoot() {
  spaceShip.Shot();
  alien.Alien_Shoot();
}

void Game::Movement() { spaceShip.Move(); }

void Game::Draw() {
  spaceShip.Draw();
  alien.Draw_Alien_Laser();
  if (!alienHit1) {
    alien.Draw_Alien1();
  }
  if (!alienHit2) {
    alien.Draw_Alien2();
  }
  if (!alienHit3) {
    alien.Draw_Alien3();
  }
  if (GameOver()) {
    DrawText("GAME OVER", 200, 200, 40, RED);
    DrawText(TextFormat("Score : %i", Best_Score()), 200, 250, 40, RED);
    if (!gameOverTriggered) {
      gameOverTimer = 2.0f;
      gameOverTriggered = true;
    }
    if (gameOverTriggered) {
      gameOverTimer -= GetFrameTime();
      if (gameOverTimer <= 0.0f) {
        exit(EXIT_SUCCESS);
      }
    }
  } else {
    Vector2 Lives_Position = {(float)GetScreenWidth() - 150, 15};
    DrawTextEx(font, TextFormat("Lives : %i", spaceShip.Lives), Lives_Position,
               25, 5, RED);
    if (Valid_Font(font)) {
      Vector2 Font_Position = Vector2{(float)GetScreenWidth() / 2 - 75, 15};
      DrawTextEx(font, TextFormat("Score : %i", Game_Score()), Font_Position,
                 25, 5, RED);
    } else {
      std::cout << "Failed to load font" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

void Game::Destroy() {
  if (Is_Destroyed) {
    UnloadFont(font);
    alien.Destroy_Alien();
  }
}

void Game::UpdateLaser() {
  spaceShip.Update_Laser();
  alien.Update_Alien_Laser();
}

int Game::Game_Score() { return Score; }
int Game::Best_Score() {

  static int New_Score = -1;
  if (New_Score == -1) {
    FILE *file = fopen("Score.txt", "r");
    if (file == NULL) {
      New_Score = 0;
    } else {
      fscanf(file, "%d", &New_Score);
      fclose(file);
    }
    if (New_Score < Score) {
      New_Score = Score;
      FILE *file = fopen("Score.txt", "w");
      fprintf(file, "%d", New_Score);
      fclose(file);
    }
  }
  return New_Score;
}
