#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>

namespace pacman {

// Game state enumeration for tracking current game phase
enum class GameState {
  MENU,    // Main menu state
  PLAYING, // Game is actively running
  PAUSED,  // Game is paused
  VICTORY, // Player has won
  LOSE,    // Player has lost
  RESET
};

// Utility struct for converting GameState to string representation
struct State {
  static constexpr const char *Menu = "MENU";
  static constexpr const char *Playing = "PLAYING";
  static constexpr const char *Paussed = "PAUSED";
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
    case GameState::PAUSED:
      return Paussed;
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
};

} // namespace pacman

#endif // GAMESTATE_HPP
