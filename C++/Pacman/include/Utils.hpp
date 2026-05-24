#ifndef UTILS_HPP
#define UTILS_HPP

#include "GameState.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#define MAX_TEXT 3

namespace pacman {

// Utility class for score management and file operations.
class Utils {
public:
  Utils();
  ~Utils();

  // Score management
  void eatPellet();                      // Increment score for regular pellet
  void eatPowerPellet();                 // Increment score for power pellet
  void printScore();                     // Print current score to console
  void writeScore(GameState &gameState); // Save score to file
  void choseOptions(sf::RenderWindow &window, GameState &gameState,
                    bool &running, sf::Text text[MAX_TEXT]);

private:
  static inline int score = 0; // Current game score
  static inline int choise = 1;
  std::string dataFilePath = "assets/data/data.txt";
};

} // namespace pacman

#endif // UTILS_HPP
