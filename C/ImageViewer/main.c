#define STB_IMAGE_IMPLEMENTATION
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stb_image.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Image Viewer"

typedef struct {
  unsigned char *data;
  int width;
  int height;
  int channels;
} ImageData;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  ImageData image;
} AppContext;

bool exit_state(SDL_Event *event, bool *running) {
  if (event == NULL || running == NULL) {
    return false;
  }

  bool exit_status = false;

  if (event->type == SDL_QUIT) {
    *running = false;
    return true;
  }

  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_RETURN:
    case SDLK_q:
      *running = false;
      exit_status = true;
      break;
    }
  }

  return exit_status;
}

bool init_sdl(AppContext *app) {
  if (app == NULL) {
    fprintf(stderr, "Error: NULL app context\n");
    return false;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
    return false;
  }

  app->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

  if (app->window == NULL) {
    fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);

  if (app->renderer == NULL) {
    fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    return false;
  }

  return true;
}

bool load_image(ImageData *image, const char *filename) {
  if (image == NULL || filename == NULL) {
    fprintf(stderr, "Error: Invalid parameters\n");
    return false;
  }

  image->data =
      stbi_load(filename, &image->width, &image->height, &image->channels, 4);

  if (image->data == NULL) {
    fprintf(stderr, "Failed to load image: %s\n", filename);
    return false;
  }

  printf("Image loaded successfully: %dx%d\n", image->width, image->height);
  return true;
}

bool create_texture(AppContext *app) {
  if (app == NULL || app->image.data == NULL) {
    fprintf(stderr, "Error: Cannot create texture\n");
    return false;
  }

  app->texture = SDL_CreateTexture(app->renderer, SDL_PIXELFORMAT_RGBA32,
                                   SDL_TEXTUREACCESS_STATIC, app->image.width,
                                   app->image.height);

  if (app->texture == NULL) {
    fprintf(stderr, "Texture creation failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetTextureScaleMode(app->texture, SDL_ScaleModeLinear);

  if (SDL_UpdateTexture(app->texture, NULL, app->image.data,
                        app->image.width * 4) != 0) {
    fprintf(stderr, "Texture update failed: %s\n", SDL_GetError());
    SDL_DestroyTexture(app->texture);
    app->texture = NULL;
    return false;
  }

  return true;
}

void load_window_icon(AppContext *app, const char *icon_path) {
  if (app == NULL || icon_path == NULL) {
    return;
  }

  SDL_Surface *icon_surface = IMG_Load(icon_path);
  if (icon_surface == NULL) {
    fprintf(stderr, "Failed to load icon: %s\n", IMG_GetError());
    return;
  }

  SDL_SetWindowIcon(app->window, icon_surface);
  SDL_FreeSurface(icon_surface);
}

void cleanup_app(AppContext *app) {
  if (app == NULL) {
    return;
  }

  if (app->image.data != NULL) {
    stbi_image_free(app->image.data);
  }

  if (app->texture != NULL) {
    SDL_DestroyTexture(app->texture);
  }

  if (app->renderer != NULL) {
    SDL_DestroyRenderer(app->renderer);
  }

  if (app->window != NULL) {
    SDL_DestroyWindow(app->window);
  }

  SDL_Quit();
}

int main(void) {
  printf("Image Viewer - Supports: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC\n");

  const char *filename = "./Images/example0.png";
  const char *icon_path = "./Icon/icon.png";

  AppContext app = {0};

  if (!init_sdl(&app)) {
    return EXIT_FAILURE;
  }

  if (!load_image(&app.image, filename)) {
    cleanup_app(&app);
    return EXIT_FAILURE;
  }

  if (!create_texture(&app)) {
    cleanup_app(&app);
    return EXIT_FAILURE;
  }

  load_window_icon(&app, icon_path);

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (exit_state(&event, &running)) {
        break;
      }
    }

    SDL_RenderClear(app.renderer);
    SDL_RenderCopy(app.renderer, app.texture, NULL, NULL);
    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
  }

  cleanup_app(&app);

  return EXIT_SUCCESS;
}
