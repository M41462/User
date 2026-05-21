#include "../include/Utils.hpp"
#include <ios>
#include <iostream>

namespace pacman {
// TODO: add shared utility functions (math helpers, conversions, etc.)
Utils::Utils() { dataFile.open(dataFilePath); }
Utils::~Utils() {}
void Utils::eatPellet() { this->score++; }
void Utils::eatPowerPellet() { this->score += 5; }
void Utils::printScore() {
  std::cout << "current Score : " << score << std::endl;
}
void Utils::writeScore() {
  try {

    dataFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    if (dataFile.is_open()) {
      dataFile << "player Score : " << score << std::endl;
      dataFile.close();
    }
    std::cout << "File written successfully." << std::endl;
  } catch (const std::ios_base::failure &e) {
    std::cerr << "I/O Error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Standard Exception: " << e.what() << std::endl;
  }
}
} // namespace pacman