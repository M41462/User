#include "Laser.hpp"

void Laser::Init_Laser(Vector2 startPos) {
  position = startPos;
  Active = true;
}

void Laser::Update_Laser() {
  if (!Active) {
    return;
  }

  position.y -= LASER_SPEED;

  if (position.y < 0) {
    Active = false;
  }
}

void Laser::Draw_Laser() {
  if (!Active) {
    return;
  }
  DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                LASER_WIDTH, LASER_HEIGHT, YELLOW);
}

bool Laser::IsCollision(Rectangle rec) {
  if (!Active) {
    return false;
  }

  const Rectangle laserRec = {position.x, position.y,
                              static_cast<float>(LASER_WIDTH),
                              static_cast<float>(LASER_HEIGHT)};

  return CheckCollisionRecs(laserRec, rec);
}
