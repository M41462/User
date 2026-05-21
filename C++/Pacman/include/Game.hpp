#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"
#include "GameState.hpp"
#include "Ghost.hpp"
#include "Map.hpp"
#include "Pacman.hpp"
#include "Utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <string_view>

namespace pacman {

// Top-level game controller. Owns the window, map, entities, and game loop.
// Manages game state, input, updates, and rendering.
class Game {
public:
  Game();
  ~Game();

  // Screen dimensions accessors
  constexpr unsigned int getWindowHeight() const { return SCREEN_HEIGHT; }
  constexpr unsigned int getWindowWidth() const { return SCREEN_WIDTH; }

  // Main game loop entry point
  void run();

private:
  Map map;             // Game map with walls, pellets, and spawn points
  Entity entity;       // Handles window icon and sound effects
  Pacman pacman;       // Player-controlled character
  GameState gameState; // Current game state (playing, paused, etc.)
  Utils utils;         // Score and file utilities
  Ghost ghosts;        // Enemy ghosts

  // Screen configuration
  static constexpr unsigned int SCREEN_HEIGHT = 992;
  static constexpr unsigned int SCREEN_WIDTH = 896;
  static constexpr std::string_view SCREEN_TITLE = "PACMAN GAME";
  static constexpr int TARGET_FPS = 60;

  sf::RenderWindow window; // Main game window
  sf::Clock windowClock;   // Tracks time for game events

  // Core game loop functions
  void processEvents(const std::optional<sf::Event> event, bool &running);
  void update(float dt); // Updates game state
  void render();         // Renders current frame
};

} // namespace pacman

#endif // GAME_HPP
