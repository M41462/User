
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

static constexpr unsigned int SCREEN_WIDTH = 750;
static constexpr unsigned int SCREEN_HEIGHT = 850;
const char WINDOW_TITLE[] = "Ping-Pong Game";

#define M_PI 3.14159265358979323846

struct Ball {
  bool IsMoving;
  bool BallHitWall;
  float x;
  float y;
  float velX;
  float velY;
  float radius;
};

struct Score {
  unsigned int player_score1;
  unsigned int player_score2;
};

struct Winner {
  bool player1;
  bool player2;
};

class UI {
  friend class Game;      // Get UI functions inside the Game class
  friend class Game_Data; // Get UI functions inside the Game_Data class

public:
  void SetContext(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
  }

  bool Init();
  void Init_Rects(SDL_FRect *Rect1, SDL_FRect *Rect2);
  void Init_Ball(struct Ball *ball);

  void Draw_Rects(SDL_Renderer *renderer, SDL_FRect &Rect1, SDL_FRect &Rect2);
  void Draw_Ball(SDL_Renderer *renderer, struct Ball ball);

  void Update_Rect(SDL_FRect &Rect, SDL_Event &event);
  void Update_Ball(struct Ball *ball);

  void Handle_AI_Movement(SDL_FRect &Rect2, struct Ball &ball);

  void Set_Window();

  UI();
  ~UI();

private:
  struct Winner winner;
  struct Ball ball;
  struct Score score;
  SDL_FRect Rect1;
  SDL_FRect Rect2;
  SDL_Surface *icon;
  SDL_Window *window;
  SDL_Renderer *renderer;
};
