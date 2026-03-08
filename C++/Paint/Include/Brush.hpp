
#define SDL_MAIN_HANDLED
#ifndef BRUSH_HPP
#define BRUSH_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <cstdint>

constexpr float MAX_BRUSH_SIZE = 20.0f;
constexpr float MIN_BRUSH_SIZE = 6.0f;

struct Mouse_Position {
  int32_t x;
  int32_t y;
};

struct Brush_Struct {
  int32_t Center_X;
  int32_t Center_Y;
  float Radius;
  bool Is_Drawing;
};

class Brush {
public:
  Mouse_Position Get_Mouse_Position() { return this->mouse_position; }
  Brush_Struct *Get_Brush_Struct() { return &this->brush_struct; }
  SDL_Color Get_Brush_Color() { return this->Brush_Color; }
  void Update_Brush_Color(SDL_Color New_Color) {
    this->Brush_Color = New_Color;
  }
  void Init_Brush();
  bool Check_Mouse_Interaction(struct Mouse_Position mouse_position,
                               SDL_FRect rect);
  void Increase_Brush_Size(SDL_Event &event, struct Brush_Struct &brush_struct);
  void Draw_Brush(SDL_Renderer *renderer);
  void Update_Brush(struct Brush_Struct *brush_struct);

private:
  static inline void Update_Brush_Size(float &radius) {
    if (radius > MAX_BRUSH_SIZE) {
      radius = MAX_BRUSH_SIZE;
    } else if (radius < MIN_BRUSH_SIZE) {
      radius = MIN_BRUSH_SIZE;
    }
  }

  static inline SDL_Color Brush_Color = {255, 255, 255, 255};
  struct Brush_Struct brush_struct = {0, 0, 0, false};
  struct Mouse_Position mouse_position = {0, 0};
};

#endif
