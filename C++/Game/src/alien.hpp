#pragma once 
#ifndef ALIEN_HPP
#define ALIEN_HPP
#include <raylib.h>
#include "./Space.hpp"

class Alien {
public:
    void Init_Alien();
    void Draw_Alien1();
    void Update_Alien_Laser();
    void Draw_Alien2();
    void Draw_Alien3();
    void Init_Alien_Laser();
    void Alien_Shoot(void);
    void Draw_Alien_Laser();
    bool IsAlienShotes(Laser laser);
    bool All_Alien_Destroyed();
    void Destroy_Alien();
    
    Texture2D alien_texture[3];
    Vector2 alien1_positions[14];
    Vector2 alien2_positions[14];
    Vector2 alien2_positions_bottom[14];
    Vector2 alien3_positions[14];
    bool alien1_active[14];
    bool alien2_active[14];
    bool alien2_active_bottom[14];
    bool alien3_active[14];
    Laser alien_laser[14];
    
    float shootTimer1;
    float shootTimer2; 
    float shootTimer3; 
    const float shootCooldown = 0.5f;
    
    float Alien3_Delay = 9.0f;  
    float Alien2_Delay = 6.0f;  
    bool Alien2_Move = false;
    bool Alien3_Move = false;
};

#endif