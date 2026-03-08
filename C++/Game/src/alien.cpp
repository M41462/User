#include "alien.hpp"
#include "Space.hpp"
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib> 
void Alien::Init_Alien() {
    alien_texture[0] = LoadTexture("../img/alien1.png");
    alien_texture[1] = LoadTexture("../img/alien2.png");
    alien_texture[2] = LoadTexture("../img/alien3.png");
    shootTimer1 = shootCooldown;
    shootTimer2 = shootCooldown;
    shootTimer3 = shootCooldown;
    bool IsAlienLoaded = true;
    if (alien_texture[0].id == 0 || alien_texture[1].id == 0 ||
        alien_texture[2].id == 0) {
        IsAlienLoaded = false;
    }
    if (!IsAlienLoaded) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }

    const int aliensPerRow = 8;
    const int screenWidth = 700;
    const int alienWidth = alien_texture[0].width;

    const float totalSpace = screenWidth - (2 * 50);
    const float spacing = (totalSpace - (aliensPerRow * alienWidth)) / (aliensPerRow - 1);
    const float startX = 50;

    for (int i = 0; i < aliensPerRow; i++) {
        alien1_positions[i] = Vector2{startX + i * (alienWidth + spacing), 50};
        alien1_active[i] = true;
        
        alien2_positions[i] = Vector2{startX + i * (alienWidth + spacing), 150};
        alien2_positions_bottom[i] = Vector2{startX + i * (alienWidth + spacing), 200};
        alien2_active[i] = true;
        alien2_active_bottom[i] = true;
        
        alien3_positions[i] = Vector2{startX + i * (alienWidth + spacing), 250};
        alien3_active[i] = true;
    }

    for (int i = aliensPerRow; i < 14; i++) {
        alien1_active[i] = false;
        alien2_active[i] = false;
        alien2_active_bottom[i] = false;
        alien3_active[i] = false;
    }

    for (int i = 0; i < 14; i++) {
        alien_laser[i].Active = false;
    }

    Alien2_Move = false;
    Alien3_Move = false;
    Alien2_Delay = 6.0f;
    Alien3_Delay = 9.0f;
}
void Alien::Draw_Alien1() {
    for (int i = 0; i < 8; i++) {
        if (alien1_active[i]) {
            DrawTexture(alien_texture[0], alien1_positions[i].x,
                        alien1_positions[i].y, WHITE);
        }
    }
}
void Alien::Draw_Alien2() {
    if (Alien2_Delay > 0) {
        Alien2_Delay -= GetFrameTime();
        if (Alien2_Delay <= 0) {
            Alien2_Move = true;
        }
    }
    for (int i = 0; i < 14; i++) {
        if (alien2_active[i]) {
            if (Alien2_Move && alien2_positions[i].y < GetScreenHeight() / 2 + 100) {
                alien2_positions[i].y += GetFrameTime() * 50;
            }
            DrawTexture(alien_texture[1], alien2_positions[i].x,
                      alien2_positions[i].y, WHITE);
        }
        
        if (alien2_active_bottom[i]) {
            if (Alien2_Move && alien2_positions_bottom[i].y < GetScreenHeight() / 2 + 150) {
                alien2_positions_bottom[i].y += GetFrameTime() * 50;
            }
            DrawTexture(alien_texture[1], alien2_positions_bottom[i].x,
                      alien2_positions_bottom[i].y, WHITE);
        }
    }
}

void Alien::Draw_Alien3() {
    if (Alien3_Delay > 0) {
        Alien3_Delay -= GetFrameTime();
        if (Alien3_Delay <= 0) {
            Alien3_Move = true;
        }
    }

    for (int i = 0; i < 14; i++) {
        if (alien3_active[i]) {
            if (Alien3_Move && alien3_positions[i].y < GetScreenHeight() / 2) {
                alien3_positions[i].y += GetFrameTime() * 50;
            }
            DrawTexture(alien_texture[2], alien3_positions[i].x,
                      alien3_positions[i].y, WHITE);
        }
    }
}
bool Alien::IsAlienShotes(Laser laser) {
  if (!laser.Active)
    return false;
  Rectangle laserRect = {laser.position.x, laser.position.y, 3, 15};

  for (int i = 0; i < 14; i++) {
    if (alien1_active[i]) {
      Rectangle alienRect = {alien1_positions[i].x, alien1_positions[i].y,
                             (float)alien_texture[0].width,
                             (float)alien_texture[0].height};
      if (CheckCollisionRecs(laserRect, alienRect)) {
        alien1_active[i] = false;
        return true;
      }
    }
  }

  for (int i = 0; i < 14; i++) {
    if (alien2_active[i]) {
      Rectangle alienRect = {alien2_positions[i].x, alien2_positions[i].y,
                             (float)alien_texture[1].width,
                             (float)alien_texture[1].height};
      if (CheckCollisionRecs(laserRect, alienRect)) {
        alien2_active[i] = false;
        return true;
      }
    }
    if (alien2_active_bottom[i]) {
      Rectangle alienRect = {
          alien2_positions_bottom[i].x, alien2_positions_bottom[i].y,
          (float)alien_texture[1].width, (float)alien_texture[1].height};
      if (CheckCollisionRecs(laserRect, alienRect)) {
        alien2_active_bottom[i] = false;
        return true;
      }
    }
  }

  for (int i = 0; i < 14; i++) {
    if (alien3_active[i]) {
      Rectangle alienRect = {alien3_positions[i].x, alien3_positions[i].y,
                             (float)alien_texture[2].width,
                             (float)alien_texture[2].height};
      if (CheckCollisionRecs(laserRect, alienRect)) {
        alien3_active[i] = false;
        return true;
      }
    }
  }
  return false;
}
bool Alien::All_Alien_Destroyed() {
  for (int i = 0; i < 14; i++) {
    if (alien1_active[i] || alien2_active[i] || alien2_active_bottom[i] ||
        alien3_active[i]) {
      return false;
    }
  }
  return true;
}

void Alien::Alien_Shoot() {
  srand(time(NULL)); 
  int attempts = 0;
  while (attempts < 14) {
    int alienIndex = rand() % 14; 
    
    if (alien1_active[alienIndex]) {
      Vector2 laserPos = {
        alien1_positions[alienIndex].x + alien_texture[0].width/2 - 1.5f,
        alien1_positions[alienIndex].y + alien_texture[0].height
      };
      alien_laser[alienIndex].Init_Laser(laserPos);
      return;
    }
    
    if (alien2_active[alienIndex]) {
      Vector2 laserPos = {
        alien2_positions[alienIndex].x + alien_texture[1].width/2 - 1.5f,
        alien2_positions[alienIndex].y + alien_texture[1].height
      };
      alien_laser[alienIndex].Init_Laser(laserPos);
      return;
    }
    
    if (alien2_active_bottom[alienIndex]) {
      Vector2 laserPos = {
        alien2_positions_bottom[alienIndex].x + alien_texture[1].width/2 - 1.5f,
        alien2_positions_bottom[alienIndex].y + alien_texture[1].height
      };
      alien_laser[alienIndex].Init_Laser(laserPos);
      return;
    }
    
    if (alien3_active[alienIndex]) {
      Vector2 laserPos = {
        alien3_positions[alienIndex].x + alien_texture[2].width/2 - 1.5f,
        alien3_positions[alienIndex].y + alien_texture[2].height
      };
      alien_laser[alienIndex].Init_Laser(laserPos);
      return;
    }
    attempts++;
  }
}

void Alien::Init_Alien_Laser(){
  for (int i = 0; i < 14; i++) {
    alien_laser[i].Init_Laser(alien1_positions[i]);
  }
}

void Alien::Update_Alien_Laser() {
    // Update timers for each alien type
    shootTimer1 -= GetFrameTime();
    shootTimer2 -= GetFrameTime();
    shootTimer3 -= GetFrameTime();

    // Alien type 1 shooting
    if (shootTimer1 <= 0.0f) {
        for (int i = 0; i < 8; i++) {  // Only 8 aliens in first row
            if (alien1_active[i] && rand() % 5 == 0) { 
                Vector2 laserPos = {
                    alien1_positions[i].x + alien_texture[0].width/2 - 1.5f,
                    alien1_positions[i].y + alien_texture[0].height
                };
                for (int j = 0; j < 14; j++) {
                    if (!alien_laser[j].Active) {
                        alien_laser[j].Init_Laser(laserPos);
                        break;
                    }
                }
            }
        }
        shootTimer1 = shootCooldown;
    }

    if (shootTimer2 <= 0.0f) {
        for (int i = 0; i < 14; i++) {
            if ((alien2_active[i] || alien2_active_bottom[i]) && rand() % 5 == 0) {
                Vector2 laserPos;
                if (alien2_active[i]) {
                    laserPos = {
                        alien2_positions[i].x + alien_texture[1].width/2 - 1.5f,
                        alien2_positions[i].y + alien_texture[1].height
                    };
                } else {
                    laserPos = {
                        alien2_positions_bottom[i].x + alien_texture[1].width/2 - 1.5f,
                        alien2_positions_bottom[i].y + alien_texture[1].height
                    };
                }
                for (int j = 0; j < 14; j++) {
                    if (!alien_laser[j].Active) {
                        alien_laser[j].Init_Laser(laserPos);
                        break;
                    }
                }
            }
        }
        shootTimer2 = shootCooldown;
    }

    if (shootTimer3 <= 0.0f) {
        for (int i = 0; i < 14; i++) {
            if (alien3_active[i] && rand() % 5 == 0) {
                Vector2 laserPos = {
                    alien3_positions[i].x + alien_texture[2].width/2 - 1.5f,
                    alien3_positions[i].y + alien_texture[2].height
                };
                for (int j = 0; j < 14; j++) {
                    if (!alien_laser[j].Active) {
                        alien_laser[j].Init_Laser(laserPos);
                        break;
                    }
                }
            }
        }
        shootTimer3 = shootCooldown;
    }
    for (int i = 0; i < 14; i++) {
        if (alien_laser[i].Active) {
            alien_laser[i].position.y += 6;
            if (alien_laser[i].position.y > GetScreenHeight()) {
                alien_laser[i].Active = false;
            }
        }
    }
}


void Alien::Draw_Alien_Laser() {
  for (int i = 0; i < 14; i++) {
    if (alien_laser[i].Active) {
      alien_laser[i].Draw_Laser();
    }
  }
}
void Alien::Destroy_Alien(){
  for (int i = 0; i < 3; i++) {
    UnloadTexture(alien_texture[i]);
  }
  for (int i = 0; i < 14; i++) {
    alien_laser[i].Active = false;
    alien_laser[i].position = {0};
  }
  Alien2_Move = false;
  Alien3_Move = false;
  Alien2_Delay = 6.0f;
  Alien3_Delay = 9.0f;
  for (int i = 0; i < 14; i++) {
    alien1_active[i] = false;
    alien2_active[i] = false;
    alien2_active_bottom[i] = false;
    alien3_active[i] = false;
  }
}
