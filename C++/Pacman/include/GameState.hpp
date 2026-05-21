#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <string>

namespace pacman {

enum class GameState { MENU, PLAYING, PAUSSED, VICTORY, LOSE };
// Game flow states. Defined but not yet used by Game.
struct State {
  GameState gameState;
  static constexpr const char *Menu = "MENU";
  static constexpr const char *Playing = "PLAYING";
  static constexpr const char *Paussed = "PAUSSED";
  static constexpr const char *Victory = "VICTORY";
  static constexpr const char *Lose = "LOSE";
  std::string getGameState() const {
    switch (gameState) {
    case GameState::MENU:
      return Menu;
    case GameState::PLAYING:
      return Playing;
    case GameState::PAUSSED:
      return Paussed;
    case GameState::VICTORY:
      return Victory;
    case GameState::LOSE:
      return Lose;

    default:
      return "Unkown";
    }
  }
};

} // namespace pacman

#endif // GAMESTATE_HPP
