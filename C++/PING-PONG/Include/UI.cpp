#include "UI.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>

UI::UI() {
  score.player_score1 = 0;
  score.player_score2 = 0;
  winner.player1 = false;
  winner.player2 = false;

  window = nullptr;
  renderer = nullptr;
  icon = nullptr;

  Rect1 = {0, 0, 0, 0};
  Rect2 = {0, 0, 0, 0};
  ball = {false, false, 0, 0, 0.0f, 0.0f, 0.0f};
}

UI::~UI() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

bool UI::Init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Log("SDL could not initialize! SDL error: %s", SDL_GetError());
    return false;
  }

  window =
      SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window) {
    SDL_Log("Window could not be created! SDL error: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_Log("Renderer could not be created! SDL error: %s", SDL_GetError());
    return false;
  }

  return true;
}

void UI::Init_Rects(SDL_FRect *Rect1, SDL_FRect *Rect2) {
  Rect1->w = 18;
  Rect1->h = Rect1->w * 10;
  Rect1->x = SCREEN_WIDTH - Rect1->w - 10;
  Rect1->y = (float)SCREEN_HEIGHT / 2 - 85;

  Rect2->w = 18;
  Rect2->h = Rect1->w * 10;
  Rect2->x = 10;
  Rect2->y = (float)SCREEN_HEIGHT / 2 - 85;
}

void UI::Init_Ball(struct Ball *ball) {
  ball->x = (float)SCREEN_WIDTH / 2;
  ball->y = (float)SCREEN_HEIGHT / 2 - 20;
  ball->velX = 2.5f;
  ball->velY = 2.5f;
  ball->radius = 25;
  ball->IsMoving = false;
  ball->BallHitWall = false;
}

void UI::Draw_Rects(SDL_Renderer *renderer, SDL_FRect &Rect1,
                    SDL_FRect &Rect2) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRectF(renderer, &Rect1);
  SDL_RenderFillRectF(renderer, &Rect2);

  SDL_RenderDrawRectF(renderer, &Rect1);
  SDL_RenderDrawRectF(renderer, &Rect2);

  for (int i = -3; i < 4; i++) {
    SDL_RenderDrawLine(renderer, (int)(SCREEN_WIDTH / 2) + i, 0,
                       (int)(SCREEN_WIDTH / 2) + i, SCREEN_HEIGHT);
  }
}

void UI::Draw_Ball(SDL_Renderer *renderer, struct Ball ball) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  while (ball.radius > 0) {
    for (int i = 0; i < 360; i++) {
      float angle = i * M_PI / 180.f;
      int x = (int)(ball.x + ball.radius * cos(angle));
      int y = (int)(ball.y + ball.radius * sin(angle));
      SDL_RenderDrawPoint(renderer, x, y);
    }
    ball.radius--;
  }
}

void UI::Update_Rect(SDL_FRect &Rect, SDL_Event &event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      Rect.y -= 15;
      break;
    case SDLK_DOWN:
      Rect.y += 15;
      break;
    default:
      break;
    }
  }
}

void UI::Handle_AI_Movement(SDL_FRect &Rect2, struct Ball &ball) {
  if (Rect2.y > ball.y + ball.radius)
    Rect2.y -= 10;
  else if (Rect2.y < ball.y - ball.radius)
    Rect2.y += 10;
}

void UI::Update_Ball(struct Ball *ball) {
  if (!ball->IsMoving)
    return;

  ball->x += ball->velX;
  ball->y += ball->velY;

  if (ball->y - ball->radius < 0) {
    ball->y = ball->radius;
    ball->velY = -ball->velY;
    ball->BallHitWall = true;
  } else if (ball->y + ball->radius > SCREEN_HEIGHT) {
    ball->y = SCREEN_HEIGHT - ball->radius;
    ball->velY = -ball->velY;
    ball->BallHitWall = true;
  } else {
    ball->BallHitWall = false;
  }
}

void UI::Set_Window() {
  if (!Init()) {
    std::cerr << "Failed to initialize window and renderer: " << SDL_GetError()
              << std::endl;
    return;
  }

  Init_Ball(&ball);
  Init_Rects(&Rect1, &Rect2);
}
