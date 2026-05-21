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

// Initializes game window, entities, and spawn positions
Game::Game() {
  sf::VideoMode mode({SCREEN_WIDTH, SCREEN_HEIGHT});
  window.create(sf::VideoMode({Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT}),
                SCREEN_TITLE.data(), sf::Style::Default);

  if (!window.isOpen()) {
    std::cerr << "Failed to create window" << std::endl;
    return;
  }

  // Configure window settings
  window.setFramerateLimit(Game::TARGET_FPS);
  window.setVerticalSyncEnabled(true);

  // Center window on screen
  sf::Vector2i desktop = sf::Vector2i(sf::VideoMode::getDesktopMode().size);
  sf::Vector2i windowPos((desktop.x - mode.size.x) / 2,
                         (desktop.y - mode.size.y) / 2);
  window.setPosition(windowPos);

  // Set initial positions for Pacman and ghosts
  pacman.setPacmanPosition(map.getPacmanSpawnPosition());
  auto spawnPositions = map.getGhostsSpawnPositions();
  for (int i = 0; i < spawnPositions.size() && i < 4; i++) {
    ghosts.setGhostsPositions(i, spawnPositions[i]);
  }

  gameState = GameState::PLAYING;
}

Game::~Game() { window.close(); }

// Main game loop - handles events, updates, and rendering
void Game::run() {
  bool running = true;
  sf::Clock deltaClock;

  // Initialize window icon and sounds
  entity.setIconWindow(window);
  if (entity.loadMenuMusic()) {
    entity.playMenuMusic();
  }

  if (!entity.loadFoodSound()) {
    std::cerr << "Game will run without pellet sound effects" << std::endl;
  }
  if (!entity.loadPowerFoodSound()) {
    std::cerr << "Game will run without power pellet sound effects"
              << std::endl;
  }

  // Game loop
  while (window.isOpen() && running) {
    // Process events
    while (const std::optional event = window.pollEvent()) {
      processEvents(event, running);
      if (map.areAllPelletsEaten()) {
        gameState = GameState::VICTORY;
      }
    }

    // Calculate delta time for frame-independent movement
    sf::Time deltaTime = deltaClock.restart();
    float dt = deltaTime.asSeconds();

    // Render current frame
    render();

    // Update game state after initial delay
    if (windowClock.getElapsedTime().asSeconds() >= 3.5f) {
      update(dt);
    }

    // Check for game over condition
    if (ghosts.ghostsPacmanCollision(pacman.getPacmanShape())) {
      gameState = GameState::LOSE;
    }
  }

  // Cleanup and save score
  utils.writeScore();
  std::cout << State::getGameState(gameState);
}

// Handles keyboard and window events
void Game::processEvents(const std::optional<sf::Event> event, bool &running) {
  if (!event) {
    return;
  }

  // Handle keyboard input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
    gameState = GameState::PAUSSED;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
    running = false;
    windowClock.restart();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::M)) {
    gameState = GameState::MENU;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P)) {
    gameState = GameState::PLAYING;
  } else if (gameState == GameState::VICTORY || gameState == GameState::LOSE) {
    running = false;
    windowClock.restart();
  }

  // Handle window close event
  if (event->is<sf::Event::Closed>()) {
    window.close();
    windowClock.restart();
  }
}

// Updates game state (movement, collisions, scoring)
void Game::update(float dt) {
  // Store previous position for collision handling
  sf::Vector2f oldPos = pacman.getPacmanPosition();

  // Update entity positions
  pacman.movement(dt, Game::TARGET_FPS);
  ghosts.movement(pacman.getPacmanPosition(), dt, Game::TARGET_FPS);

  // Handle wall collisions
  if (map.isWallCollision(pacman.getPacmanShape())) {
    pacman.setPacmanPosition(oldPos);
  }

  // Check for pellet collisions and update score
  int ate = map.checkPelletCollision(pacman.getPacmanShape());
  if (ate == 1) { // Regular pellet
    entity.playFoodSound();
    utils.eatPellet();
  } else if (ate == 2) { // Power pellet
    entity.playPowerFoodSound();
    utils.eatPowerPellet();
  }
}

// Renders the current game frame
void Game::render() {
  window.clear(sf::Color::Black);
  map.drawMap(window);
  pacman.drawPacman(window);
  ghosts.drawGhosts(window);
  window.display();
}

} // namespace pacman
