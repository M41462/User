#ifndef LASER_HPP
#define LASER_HPP
#include <raylib.h>
class Laser {
public:
  void Init_Laser(Vector2 startPos);
  void Update_Laser();
  void Draw_Laser();
  bool IsCollision(Rectangle rec);
  bool Active = false;
  Vector2 position;
};
#endif // LASER_HPP 
