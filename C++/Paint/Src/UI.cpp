// UI.cpp - Manages SDL window, events, and rendering.
#include "../Include/UI.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <cstdint>
#include <iostream>

UI::UI() {
  // Init members
  window = nullptr;
  renderer = nullptr;
  texture = nullptr;
  event = new SDL_Event;
  rects.resize(9);
  lastDrawX = -1;
  lastDrawY = -1;
  Change_Background = false;
}

UI::~UI() {
  // Cleanup SDL resources
  if (window != nullptr)
    SDL_DestroyWindow(window);
  if (renderer != nullptr)
    SDL_DestroyRenderer(renderer);
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
  if (event != nullptr)
    delete event;
  SDL_Quit();
}

void UI::Load_Icon() {
  // Load window icon
  SDL_Surface *icon = IMG_Load(Icon_Path.c_str());
  if (icon == nullptr) {
    std::cerr << "Error loading icon: " << SDL_GetError() << std::endl;
    return;
  }
  SDL_SetWindowIcon(window, icon);
  SDL_FreeSurface(icon);
}

void UI::Event_Handler(SDL_Event &event, bool &running) {
  // Handle quit, mouse, and key events
  switch (event.type) {
  case SDL_QUIT:
    running = false;
    break;

  case SDL_MOUSEBUTTONDOWN:
    // change brush color
    if (event.button.button == SDL_BUTTON_LEFT) {
      brush.Get_Brush_Struct()->Is_Drawing = true;
    }
    break;

  case SDL_MOUSEBUTTONUP:
    if (event.button.button == SDL_BUTTON_LEFT) {
      brush.Get_Brush_Struct()->Is_Drawing = false;
      lastDrawX = -1;
      lastDrawY = -1;
    }
    break;
  }

  // Handle keyboard events
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      running = false; // Quit
      break;
    case SDLK_q:
      running = false; // Quit
      break;
    case SDLK_s:
      save.Save_To_Png(renderer, texture); // Save to PNG
      break;
    case SDLK_RETURN:
      Change_Background = true; // flag for clearing the screen
      break;
    }
  }
}

void UI::Init_Color_Box() {
  // Setup color box positions
  for (int i = 0; i < 9; i++) {
    rects[i] = {.x = (float)i * 50, .y = 0, .w = 50, .h = 50};
  }
}

void UI::Draw_Color_Box() {
  SDL_Color colors[9] = {
      {0, 0, 0, 255},       // Black
      {255, 255, 255, 255}, // White
      {255, 0, 0, 255},     // Red
      {0, 255, 0, 255},     // Green
      {0, 0, 255, 255},     // Blue
      {255, 255, 0, 255},   // Yellow
      {255, 0, 255, 255},   // Magenta
      {0, 255, 255, 255},   // Cyan
      {255, 165, 0, 255},   // Orange
  };
  for (int i = 0; i < 9; i++) {
    SDL_FRect &rect = rects[i];
    SDL_Color &color = colors[i];

    // Draw filled rectangle
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Check if mouse is over this color box and left button is pressed
    if (brush.Check_Mouse_Interaction(brush.Get_Mouse_Position(), rects[i]) &&
        brush.Get_Brush_Struct()->Is_Drawing) {

      brush.Update_Brush_Color(color); // Update brush color
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer, &rect);

    // Draw outline
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRectF(renderer, &rect);
  }
}

bool UI::Init_Window() {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Window Init Error: " << SDL_GetError() << std::endl;
    return false;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Renderer Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH,
                              WINDOW_HEIGHT);

  if (texture == nullptr) {
    std::cerr << "Texture Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_SetWindowResizable(window, SDL_TRUE); // Allow window resizing
  Load_Icon();                              // Load icon for the window
  brush.Init_Brush();
  Init_Color_Box();
  return true;
}

void UI::Draw_To_Texture(int x, int y, int radius, SDL_Color color) {

  void *pixels;
  int pitch;
  if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
    std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
    return;
  }

  uint32_t *pixelData = (uint32_t *)pixels;
  uint32_t brushColor =
      (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;

  Draw_Circle_To_Pixels(pixelData, pitch, x, y, radius, brushColor);

  SDL_UnlockTexture(texture);
}

void UI::Draw_Circle_To_Pixels(uint32_t *pixelData, int pitch, int x, int y,
                               int radius, uint32_t brushColor) {
  int startX = std::max(0, x - radius);
  int endX = std::min(WINDOW_WIDTH - 1, x + radius);
  int startY = std::max(0, y - radius);
  int endY = std::min(WINDOW_HEIGHT - 1, y + radius);

  for (int px = startX; px <= endX; ++px) {
    for (int py = startY; py <= endY; ++py) {
      int dx = px - x;
      int dy = py - y;
      if (dx * dx + dy * dy <= radius * radius) {
        pixelData[py * (pitch / 4) + px] = brushColor;
      }
    }
  }
}

void UI::Draw_Line_To_Texture(int x1, int y1, int x2, int y2, int radius,
                              SDL_Color color) {
  void *pixels;
  int pitch;
  if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
    std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
    return;
  }

  uint32_t *pixelData = (uint32_t *)pixels;
  uint32_t brushColor =
      (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    Draw_Circle_To_Pixels(pixelData, pitch, x1, y1, radius, brushColor);
    if (x1 == x2 && y1 == y2)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }

  SDL_UnlockTexture(texture);
}

void UI::Clear_Screen() {
  void *pixels;
  int pitch;
  if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
    std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
    return;
  }

  uint32_t *pixelData = (uint32_t *)pixels;
  uint32_t bgColor = 0x000000FF;

  for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i) {
    pixelData[i] = bgColor;
  }

  SDL_UnlockTexture(texture);
}

void UI::Run() {

  bool running = true;
  while (running) {
    while (SDL_PollEvent(event)) {
      Event_Handler(*event, running);
      brush.Increase_Brush_Size(*event, *brush.Get_Brush_Struct());
    }
    brush.Update_Brush(brush.Get_Brush_Struct());

    SDL_SetRenderDrawColor(renderer, Window_Color.r, Window_Color.g,
                           Window_Color.b,
                           Window_Color.a); // Set background color

    SDL_RenderClear(renderer);

    if (Change_Background) {
      Clear_Screen();
      Change_Background = false;
      std::cout << "Reset background" << std::endl;
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    Draw_Color_Box();
    brush.Draw_Brush(renderer);

    if (brush.Get_Brush_Struct()->Is_Drawing) {
      int currX = brush.Get_Brush_Struct()->Center_X;
      int currY = brush.Get_Brush_Struct()->Center_Y;
      int radius = brush.Get_Brush_Struct()->Radius;
      SDL_Color color = brush.Get_Brush_Color();
      if (lastDrawX != -1) {
        Draw_Line_To_Texture(lastDrawX, lastDrawY, currX, currY, radius, color);
      } else {
        Draw_To_Texture(currX, currY, radius, color);
      }
      lastDrawX = currX;
      lastDrawY = currY;
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16); // Delay for 60 FPS
  }
}
