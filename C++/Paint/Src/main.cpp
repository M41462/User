
// main.cpp - Entry point for the Paint app.
// Initialize the window and run the application if successful
#define SDL_MAIN_HANDELED
#include "../Include/UI.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  // Suppress unused warnings
  (void)argv;
  (void)argc;

  // Create UI instance
  UI ui;

  // Initialize the window and run the application if successful
  if (ui.Init_Window()) {
    ui.Run();
  } else {
    std::cerr << "Application failed to initialize." << std::endl;
    return -1;
  }

  return 0;
}
