#include "Laser.hpp"

void Laser::Init_Laser(Vector2 startPos) {
  position = startPos;
  Active = true;
}

void Laser::Update_Laser() {
  if (Active) {
    position.y -= 10;

    if (position.y < 0) {
      Active = false;
    }
  }
}
void Laser::Draw_Laser() {
  if (Active) {
    DrawRectangle(position.x, position.y, 3, 15, YELLOW);
  }
}

bool Laser::IsCollision(Rectangle rec){
  if (!Active){
    return false; 
  }
  Rectangle Laser_Rec = {position.x, position.y, 3, 15};
  return CheckCollisionRecs(Laser_Rec , rec); 
}
