#include "../Include/Save.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_test_images.h>
#include <iostream>

bool Save::Is_Save_Name_Valid() {
  // Check if filename is unique
  std::string test_path =
      "../Saves/" + Save_Name + "_" + std::to_string(Save_Number) + ".png";

  FILE *file = fopen(test_path.c_str(), "r");
  if (file) {
    fclose(file);
    return false; // file exists
  }
  return true;
}

std::string Save::Set_Save_Name() {
  // Generate unique save path
  while (!Is_Save_Name_Valid() && Save_Number <= 15) {
    Save_Number++;
  }

  Save_Path =
      "../Saves/" + Save_Name + "_" + std::to_string(Save_Number) + ".png";

  return Save_Path;
}

void Save::Save_To_Png(SDL_Renderer *renderer, SDL_Texture *texture) {

  // Save texture to PNG
  if (!renderer || !texture) {
    std::cerr << "Renderer or texture is null" << std::endl;
    return;
  }

  Save_Path = Set_Save_Name();

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                                        SDL_PIXELFORMAT_RGBA32);

  if (!surface) {
    std::cerr << "Create surface failed: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_Texture *old_target = SDL_GetRenderTarget(renderer);
  SDL_SetRenderTarget(renderer, texture);

  if (SDL_RenderReadPixels(renderer, NULL, surface->format->format,
                           surface->pixels, surface->pitch) != 0) {
    std::cerr << "ReadPixels failed: " << SDL_GetError() << std::endl;
    SDL_SetRenderTarget(renderer, old_target);
    SDL_FreeSurface(surface);
    return;
  }

  SDL_SetRenderTarget(renderer, old_target);
  if (Save_Number > 15) {
    SDL_FreeSurface(surface);
    std::cerr << "Too many saves" << std::endl;
    return;
  }

  if (SDL_SaveBMP(surface, Save_Path.c_str()) != 0) {
    std::cerr << "Save PNG failed: " << SDL_GetError() << std::endl;
  } else {
    std::cout << "Saved to " << Save_Path << std::endl;
  }

  SDL_FreeSurface(surface);
}
