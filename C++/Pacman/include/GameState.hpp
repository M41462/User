#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace pacman {

// Game state enumeration for tracking current game phase
enum class GameState {
  MENU,    // Main menu state
  PLAYING, // Game is actively running
  VICTORY, // Player has won
  LOSE,    // Player has lost
  RESET
};

// Utility struct for converting GameState to string representation
struct State {
  static constexpr const char *Menu = "MENU";
  static constexpr const char *Playing = "PLAYING";
  static constexpr const char *Victory = "VICTORY";
  static constexpr const char *Lose = "LOSE";
  static constexpr const char *Reset = "RESET";

  // Converts GameState enum to human-readable string
  static const std::string getGameState(GameState gameState) {
    switch (gameState) {
    case GameState::MENU:
      return Menu;
    case GameState::PLAYING:
      return Playing;
    case GameState::VICTORY:
      return Victory;
    case GameState::LOSE:
      return Lose;
    case GameState::RESET:
      return Reset;
    default:
      return "Unknown";
    }
  }
  void drawGameStatus(sf::RenderWindow &window, GameState &gameState,
                      sf::Text &winText, sf::Text &loseText) {
    if (gameState == GameState::VICTORY) {
      winText.setPosition({350, 1010});
      window.draw(winText);
    } else if (gameState == GameState::LOSE) {
      loseText.setPosition({270, 1010});
      window.draw(loseText);
    }
  }
};

} // namespace pacman

#endif // GAMESTATE_HPP
