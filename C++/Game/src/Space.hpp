#pragma once

#include <raylib.h>

#include "Laser.hpp"

class SpaceShip {
public:
  static constexpr int MAX_LIVES = 3;
  static constexpr int MOVE_SPEED = 10;
  static constexpr int BOUNDARY_OFFSET = 50;

  SpaceShip();
  ~SpaceShip();

  void Draw();
  void Move();
  void IsCollision();
  void Shot();
  void Update_Laser();

  Vector2 position = {0};
  Laser laser;
  Texture2D image = {0};
  int Lives = MAX_LIVES;

private:
  static bool isTextureValid(const Texture2D &texture) {
    return texture.id != 0;
  }
};
