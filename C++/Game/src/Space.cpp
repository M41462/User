#include "./Space.hpp"
#include <iostream>
SpaceShip::SpaceShip() {
  image = LoadTexture("../img/spaceship.png");
  if (image.id == 0) {
    std::cout << "Failed to load image" << std::endl;
    exit(1);
  }
  position.x = (float)GetScreenWidth() / 2;
  position.y = (float)GetScreenHeight() - 25;
}
SpaceShip::~SpaceShip() { UnloadTexture(image); }
void SpaceShip::Draw() {
  DrawTexture(image, position.x, position.y, WHITE);
  if (laser.Active) {
    laser.Draw_Laser();
  }
}

void SpaceShip::IsCollision() {
  if (position.x > GetScreenWidth() - 50) {
    position.x = GetScreenWidth() - 50;
  } else if (position.x < 0) {
    position.x = 0;
  }
}

void SpaceShip::Move() {
  if (Lives > 0) {
    if (IsKeyDown(KEY_LEFT)) {
      position.x -= 10;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      position.x += 10;
    }
  }
}
void SpaceShip::Shot() {
  if (!laser.Active) {
    Vector2 laserPos = {position.x + (float)image.width / 2 - 1.5f, position.y};
    laser.Init_Laser(laserPos);
    laser.Active = true;
  }
}
void SpaceShip::Update_Laser() {
  if (laser.Active) {
    laser.Update_Laser();
  }
}
