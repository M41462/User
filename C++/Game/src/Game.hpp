#include <raylib.h>
#include "Space.hpp"
#include "alien.hpp"

#ifndef GAME_HPP
#define GAME_HPP
extern Sound Alien_Sound;
extern bool Is_Destroyed;

class Game {
public:
  Game();
  ~Game();
  void Movement();
  void Draw();
  void IsCollision();
  void Destroy();
  int Game_Score();
  bool IsSpaceShipHitByAlienLaser(); 
  int Best_Score();
  void Shoot();
  bool GameOver();
  void UpdateLaser();
private:
  SpaceShip spaceShip;
  bool alienHit1 = false;
  Font font = LoadFont("../Font/Score_Font.ttf");
  bool alienHit2 = false;
  bool alienHit3 = false;
  Alien alien;
  int Score = 0;
  float gameOverTimer = 0.0f;
  bool gameOverTriggered = false;
};

#endif
