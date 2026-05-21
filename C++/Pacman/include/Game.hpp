#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include "GameState.hpp"
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
class Game {
public:
  Game();
  ~Game();

  constexpr unsigned int getWindowHeight() { return SCREEN_HEIGHT; }
  constexpr unsigned int getWindowWidth() { return SCREEN_WIDTH; }

  void run();

private:
  Map map;
  Entity entity;
  Pacman pacman;
  GameState gameState;
  Utils utils; 

  static constexpr unsigned int SCREEN_HEIGHT = 992;
  static constexpr unsigned int SCREEN_WIDTH = 896;
  static constexpr std::string_view SCREEN_TITLE = "PACMAN GAME";
  static constexpr int TARGET_FPS = 60;
  sf::RenderWindow window;
  sf::Clock windowClock; 
  void processEvents(const std::optional<sf::Event> event, bool &running);
  void update(float dt);
  void render();
};

} // namespace pacman

#endif // GAME_HPP
