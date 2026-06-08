#include <iostream>

#include "../include/Game.hpp"

int main(int argc, char *argv[]) {
  Game game;
  try {
    game.run();
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
