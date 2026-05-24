#include "../include/Utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>
#include <ostream>

namespace pacman {

Utils::Utils() {}
Utils::~Utils() {}

void Utils::eatPellet() { score++; }

void Utils::eatPowerPellet() { score += 5; }

void Utils::printScore() {
  std::cout << "current Score : " << score << std::endl;
}

void Utils::writeScore(GameState &gameState) {
  std::ofstream dataFile(dataFilePath);
  if (dataFile.is_open()) {
    dataFile << "player Score : " << score << std::endl;
    dataFile << "Game Status : " << State::getGameState(gameState)
             << std::endl;
  }
}

static inline void writeText(sf::RenderWindow &window,
                             sf::Text text[MAX_TEXT]) {
  for (int i = 0; i < MAX_TEXT; i++) {
    window.draw(text[i]);
  }
}

void Utils::choseOptions(sf::RenderWindow &window, GameState &gameState,
                         bool &running, sf::Text text[MAX_TEXT]) {
  if (gameState != GameState::MENU)
    return;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
    choise--;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
    choise++;

  if (choise < 1)
    choise = 1;
  if (choise > 2)
    choise = 2;

  switch (choise) {
  case 1:
    text[0].setFillColor(sf::Color::White);
    text[1].setFillColor(sf::Color::Green);
    text[2].setFillColor(sf::Color::White);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
      gameState = GameState::PLAYING;
    break;
  case 2:
    text[0].setFillColor(sf::Color::White);
    text[1].setFillColor(sf::Color::White);
    text[2].setFillColor(sf::Color::Green);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
      running = false;
    break;
  default:
    break;
  }
  writeText(window, text);
}

} // namespace pacman
