#include "../include/Game.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

namespace pacman {

// Initializes game window, entities, and spawn positions
Game::Game() {
  sf::VideoMode mode({SCREEN_WIDTH, SCREEN_HEIGHT});
  window.create(sf::VideoMode({Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT}),
                SCREEN_TITLE.data(), sf::Style::Default);

  if (!window.isOpen()) {
    throw std::runtime_error("Error opening window");
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

  gameState = GameState::MENU;
}

inline void checkResources(sf::RenderWindow &window, Entity &entity,
                           Pacman &pacman, Ghost &ghosts) {
  try {
    entity.setIconWindow(window);
  } catch (const std::exception &e) {
    std::cerr << "Warning: " << e.what() << " (no icon)" << std::endl;
  }
  try {
    pacman.loadPacmanTextures();
  } catch (const std::exception &e) {
    std::cerr << "Error loading pacman texture" << std::endl;
  }
  try {
    ghosts.initGhosts();
  } catch (const std::exception &e) {
    std::cerr << "Error loading ghosts texture" << std::endl;
  }

  try {
    entity.loadMenuMusic();
    entity.playMenuMusic();
  } catch (const std::exception &e) {
    std::cerr << "Warning: " << e.what() << std::endl;
  }

  try {
    entity.loadFoodSound();
  } catch (const std::exception &e) {
    std::cerr << "Game will run without pellet sound" << std::endl;
  }

  try {
    entity.loadPowerFoodSound();
  } catch (const std::exception &e) {
    std::cerr << "Game will run without power pellet sound" << std::endl;
  }

  try {
    entity.loadPacmanDeathSound();
  } catch (const std::exception &e) {
    std::cerr << "Game will run without death sound" << std::endl;
  }

  try {
    entity.initGameFont();
  } catch (const std::exception &e) {
    std::cerr << "Warning: " << e.what() << " (no font)" << std::endl;
  }
}

// Destructor: closes the SFML window; all other resources are RAII-cleaned.
Game::~Game() { window.close(); }

// Main game loop - handles events, updates, and rendering
void Game::run() {
  bool running = true;
  sf::Clock deltaClock;

  checkResources(window, entity, pacman, ghosts);
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
    render(running);

    // Update game state after initial delay
    if (windowClock.getElapsedTime().asSeconds() >= 3.5f) {
      if (ghosts.ghostsPacmanCollision(pacman.getPacmanShape()) &&
          windowClock.getElapsedTime().asSeconds() >= 1.5) {
        gameState = GameState::RESET;
        pacman.setLives();

        entity.playPacmanDeathSound();
        windowClock.restart();
      }
      update(dt);
      if (gameState == GameState::RESET) {
        pacman.setPacmanPosition(map.getPacmanSpawnPosition());
        gameState = GameState::PLAYING;
      }
    }
  }

  // Cleanup and save score
  utils.writeScore(gameState);
}

// Process window events and keyboard input; updates gameState and running flag.
void Game::processEvents(const std::optional<sf::Event> event, bool &running) {
  if (!event) {
    return;
  }
  // Handle keyboard input
  switch (gameState) {
  case GameState::VICTORY:
  case GameState::LOSE:
    running = false;
    windowClock.restart();
    break;

  default:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
      gameState = GameState::MENU;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
      running = false;
      windowClock.restart();
    }
    break;
  }
  // Handle window close event
  if (event->is<sf::Event::Closed>()) {
    window.close();
    windowClock.restart();
  }
}

// Update entities, handle collisions, and manage game state.
void Game::update(float dt) {
  // Store previous position for collision handling
  sf::Vector2f oldPacmanPos = pacman.getPacmanPosition();
  std::vector<sf::Vector2f> oldGhostsPos(MAX_GHOSTS);
  for (int i = 0; i < MAX_GHOSTS; i++)
    oldGhostsPos[i] = ghosts.getGhostsPositions(i);

  // Update entity positions
  pacman.movement(dt, Game::TARGET_FPS, gameState);
  ghosts.movement(pacman.getPacmanPosition(), dt, Game::TARGET_FPS);
  sf::Vector2f test = ghosts.getGhostsPositions(0);

  // Handle wall collisions
  if (map.isWallCollision(pacman.getPacmanShape())) {
    pacman.setPacmanPosition(oldPacmanPos);
  }
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (map.isWallCollision(ghosts.getGhostShape(i))) {
      ghosts.setGhostsPositions(i, oldGhostsPos[i]);
    }
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
  if (pacman.getPacmanLives() <= 0) {
    gameState = GameState::LOSE;
  }
}

// Render one frame: clear, draw map, Pacman, ghosts, UI, then display.
void Game::render(bool &running) {
  window.clear(sf::Color::Black);
  map.drawMap(window);
  pacman.drawPacman(window);
  ghosts.drawGhosts(window);
  entity.drawGameFont(window, gameState, utils, running);

  sf::RectangleShape debugRect = pacman.getDebugRectangle();
  window.draw(debugRect);
  window.display();
}

} // namespace pacman
