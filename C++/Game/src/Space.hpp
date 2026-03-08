#pragma once
#include <raylib.h>
#include "Laser.hpp"
#include "alien.hpp"

class SpaceShip {
public:
  SpaceShip();
  ~SpaceShip();
  void Draw();
  void Move();
  void IsCollision();
  void Shot();
  void Update_Laser();
  Vector2 position;
  Laser laser;
  Texture2D image;
  int Lives = 3;
};
