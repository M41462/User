#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED
#include "stb_image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Image Viewer"

typedef struct {
  unsigned char *data;
  int width;
  int height;
  int channels;
} ImageStruct;

static inline bool ExitState(SDL_Event *event, bool *running) {
  if (event->type == SDL_QUIT)
    *running = false;
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_RETURN:
    case SDLK_q:
      *running = false;
      break;
    }
  }
  return running;
}

bool InitSDL(SDL_Window **window, SDL_Renderer **renderer) {

  if (!window || !renderer) {
    perror("NULL pointer for window or renderer");
    return false;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    perror("Error Init SDL2");
    return false;
  }

  *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                             WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

  if (!*window) {
    perror("Error creating window");
    return false;
  }

  *renderer = SDL_CreateRenderer(*window, 0, SDL_RENDERER_ACCELERATED);

  if (!*renderer) {
    perror("Error creating renderer");
    return false;
  }

  return true;
}

bool InitImage(ImageStruct *image, const char *filename) {

  image->data =
      stbi_load(filename, &image->width, &image->height, &image->channels, 4);

  if (image->data) {
    perror("Image loaded Successfully");
    return true;
  } else {
    perror("Image loading Failed");
    return false;
  }
}

int main(int argc, char *argv[]) {

  printf("image loading from file/memory: JPG, PNG, TGA, BMP, PSD, "
         "GIF, HDR, PIC\n");

  const char *filename = "./Images/example.png";
  const char *icon = "./Icon/icon.png";
  ImageStruct image;
  SDL_Window *window;
  SDL_Renderer *renderer;

  if (!InitSDL(&window, &renderer) || !InitImage(&image, filename)) {
    return EXIT_FAILURE;
  }

  SDL_Surface *iconSurface = IMG_Load(icon);
  if (!iconSurface) {
    SDL_Log("Failed to load icon: %s", IMG_GetError());
  } else {
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
  }

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_STATIC, image.width, image.height);
  if (!texture) {
    printf("Error creating texture\n");
    return EXIT_FAILURE;
  }

  SDL_UpdateTexture(texture, NULL, image.data, image.width * 4);

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (ExitState(&event, &running)) {
        break;
      }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  // Free image data and destroy SDL resources
  stbi_image_free(image.data);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
