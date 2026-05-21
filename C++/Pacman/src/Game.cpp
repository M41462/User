#include "../include/Game.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>
#include <optional>
namespace pacman {

Game::Game() {

  sf::VideoMode mode({SCREEN_WIDTH, SCREEN_HEIGHT});
  window.create(sf::VideoMode({Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT}),
                SCREEN_TITLE.data(), sf::Style::Default);

  if (!window.isOpen()) {
    std::cerr << "Failed to create window" << std::endl;
    return;
  }

  window.setFramerateLimit(Game::TARGET_FPS);
  window.setVerticalSyncEnabled(true);
  sf::Vector2i desktop = sf::Vector2i(sf::VideoMode::getDesktopMode().size);

  sf::Vector2i windowPos((desktop.x - mode.size.x) / 2,
                         (desktop.y - mode.size.y) / 2);

  window.setPosition(windowPos);
  pacman.setPacmanPosition(map.getSpawnPosition());

  gameState = GameState::PLAYING;
}

Game::~Game() { window.close(); }

// ── Main game loop ──
void Game::run() {
  bool running = true;
  sf::Clock deltaClock;
  entity.setIconWindow(window);
  if (entity.loadMenuMusic())
    entity.playMenuMusic();

  if (!entity.loadFoodSound())
    std::cerr << "Game will run without pellet sound effects" << std::endl;
  if (!entity.loadPowerFoodSound())
    std::cerr << "Game will run without power pellet sound effects" << std::endl;

  while (window.isOpen() && running) {
    while (const std::optional event = window.pollEvent()) {
      if (map.areAllPelletsEaten())
        gameState = GameState::VICTORY;
      processEvents(event, running);
    }
    sf::Time deltaTime = deltaClock.restart();
    float dt = deltaTime.asSeconds();
    render(); 
    if (windowClock.getElapsedTime().asSeconds() >= 3.5f)
      update(dt); 
  }
  utils.writeScore(); 
}

// ── Event handling ──
void Game::processEvents(const std::optional<sf::Event> event, bool &running) {
  if (!event)
    return;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
    running = false;
    windowClock.restart(); 
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
    running = false;
    windowClock.restart(); 
  } else if (gameState == GameState::VICTORY || gameState == GameState::LOSE) {
    running = false;
    windowClock.restart(); 
  }
  if (event->is<sf::Event::Closed>()){
    window.close();
    windowClock.restart();
  } 
}

// ── Update logic ──
void Game::update(float dt) {
  sf::Vector2f oldPos = pacman.getPacmanPosition();
  pacman.movement(dt, Game::TARGET_FPS);
  if (map.isWallCollision(pacman.getPacmanShape()))
    pacman.setPacmanPosition(oldPos);
  int ate = map.checkPelletCollision(pacman.getPacmanShape());
  if (ate == 1) {
    entity.playFoodSound();
    utils.eatPellet(); 
  } else if (ate == 2) {
    entity.playPowerFoodSound();
    utils.eatPowerPellet(); 
  }
  utils.printScore(); 
}

// ── Render frame ──
void Game::render() {
  window.clear(sf::Color::Black);
  map.drawMap(window);
  pacman.drawPacman(window);
  window.display();
}

} // namespace pacman
