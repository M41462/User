#include "../include/Utils.hpp"
#include <ios>
#include <iostream>

namespace pacman {

// Initializes file stream for score saving
Utils::Utils() { dataFile.open(dataFilePath); }

Utils::~Utils() {}

// Increments score when a regular pellet is eaten
void Utils::eatPellet() { score++; }

// Increments score when a power pellet is eaten (5 points)
void Utils::eatPowerPellet() { score += 5; }

// Prints current score to console
void Utils::printScore() {
  std::cout << "current Score : " << score << std::endl;
}

// Writes final score to file with error handling
void Utils::writeScore() {
  try {
    dataFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    if (dataFile.is_open()) {
      dataFile << "player Score : " << score << std::endl;
      dataFile.close();
    }
  } catch (const std::ios_base::failure &e) {
    std::cerr << "I/O Error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Standard Exception: " << e.what() << std::endl;
  }
}

} // namespace pacman
