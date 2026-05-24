// Entry point: creates the Game controller and starts the main loop.
#include "../include/Game.hpp"
#include <iostream>

int main() { // Game execution starts here
  try {
    pacman::Game game;
    game.run();
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
