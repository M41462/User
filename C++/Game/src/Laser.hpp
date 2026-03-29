#ifndef LASER_HPP
#define LASER_HPP

#include <raylib.h>

class Laser {
public:
  static constexpr int LASER_WIDTH = 3;
  static constexpr int LASER_HEIGHT = 15;
  static constexpr int LASER_SPEED = 10;

  void Init_Laser(Vector2 startPos);
  void Update_Laser();
  void Draw_Laser();
  bool IsCollision(Rectangle rec);

  bool Active = false;
  Vector2 position = {0};
};

#endif
