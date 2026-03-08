// Brush.cpp - Handles brush drawing, position, and size adjustments.
#include "../Include/Brush.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

void Brush::Init_Brush() {
  // Set default brush properties
  brush_struct = {
      .Center_X = 395, .Center_Y = 345, .Radius = 8, .Is_Drawing = false};
}

void Brush::Draw_Brush(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, Brush_Color.r, Brush_Color.g, Brush_Color.b,
                         Brush_Color.a);
  int32_t x = brush_struct.Radius - 1;
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = tx - (brush_struct.Radius * 2);

  while (x >= y) {
    // Render circle lines
    SDL_RenderDrawLine(renderer, brush_struct.Center_X - x,
                       brush_struct.Center_Y - y, brush_struct.Center_X + x,
                       brush_struct.Center_Y - y);
    SDL_RenderDrawLine(renderer, brush_struct.Center_X - x,
                       brush_struct.Center_Y + y, brush_struct.Center_X + x,
                       brush_struct.Center_Y + y);

    SDL_RenderDrawLine(renderer, brush_struct.Center_X - y,
                       brush_struct.Center_Y - x, brush_struct.Center_X + y,
                       brush_struct.Center_Y - x);
    SDL_RenderDrawLine(renderer, brush_struct.Center_X - y,
                       brush_struct.Center_Y + x, brush_struct.Center_X + y,
                       brush_struct.Center_Y + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }
    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - (brush_struct.Radius * 2));
    }
  }
}

void Brush::Update_Brush(struct Brush_Struct *brush_struct) {
  // Update position to mouse location
  if (!brush_struct)
    return;
  SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
  brush_struct->Center_X = mouse_position.x;
  brush_struct->Center_Y = mouse_position.y;
}

bool Brush::Check_Mouse_Interaction(struct Mouse_Position mouse_position,
                                    SDL_FRect rect) {
  // Check if mouse is inside rect
  return (mouse_position.x >= rect.x && mouse_position.x <= rect.x + rect.w &&
          mouse_position.y >= rect.y && mouse_position.y <= rect.y + rect.h);
}

void Brush::Increase_Brush_Size(SDL_Event &event,
                                struct Brush_Struct &brush_struct) {
  // Adjust size with UP/DOWN keys
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP) {
      brush_struct.Radius += 2;
      Update_Brush_Size(brush_struct.Radius); // Update Brush Size
    }
    if (event.key.keysym.sym == SDLK_DOWN) {
      brush_struct.Radius -= 2;
      Update_Brush_Size(brush_struct.Radius); // Update Brush Size
    }
  }
}
