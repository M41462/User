#include "../include/Entity.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

namespace pacman {

// Constructor – initialise audio buffers, set default volumes, enable font smoothing, and configure menu text.
Entity::Entity()
    : foodSound(eatBuffer), powerFoodSound(powerEatBuffer),
      deathSound(deathBuffer), title(gameFont), play(gameFont), exit(gameFont) {
  startMusic.setVolume(30.f); // Background music volume
  foodSound.setVolume(30.f);  // Sound effect volume
  gameFont.setSmooth(true);

  title.setCharacterSize(40);
  play.setCharacterSize(40);
  exit.setCharacterSize(40);

  title.setPosition({330.f, 150.f});
  play.setPosition({370.f, 350.f});
  exit.setPosition({370.f, 550.f});

  title.setString("PACMAN");
  play.setString("Play");
  exit.setString("Exit");
}

// Destructor: SFML resources (fonts, sounds, textures) are RAII-managed and released automatically.
Entity::~Entity() {}

// Load and set the window icon from assets/game.png (error logged if missing).
void Entity::setIconWindow(sf::RenderWindow &window) {
  if (icon.loadFromFile("assets/game.png")) {
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
  } else {
    std::cerr << "Error loading window icon" << std::endl;
  }
}

// Load menu background music; returns false and logs an error on failure.
bool Entity::loadMenuMusic() {
  if (!startMusic.openFromFile(menuMusicPath.c_str())) {
    std::cerr << "Error playing music" << std::endl;
    return false;
  }
  return true;
}

// Plays menu background music
void Entity::playMenuMusic() { startMusic.play(); }

// Load sound for regular pellets; logs error on failure.
bool Entity::loadFoodSound() {
  if (!eatBuffer.loadFromFile(eatPelletPath)) {
    std::cerr << "Error loading food sound" << std::endl;
    return false;
  }
  return true;
}

// Load sound for power pellets; logs error on failure.
bool Entity::loadPowerFoodSound() {
  if (!powerEatBuffer.loadFromFile(eatPowerPelletPath)) {
    std::cerr << "Error loading power pellet sound" << std::endl;
    return false;
  }
  return true;
}

// Plays sound effect for regular pellet collection (if not already playing)
void Entity::playFoodSound() {
  if (foodSound.getStatus() != sf::Sound::Status::Playing) {
    foodSound.play();
  }
}

// Plays sound effect for power pellet collection (if not already playing)
void Entity::playPowerFoodSound() {
  if (powerFoodSound.getStatus() != sf::Sound::Status::Playing) {
    powerFoodSound.play();
  }
}

// Load sound for Pacman's death. Logs error on failure.
bool Entity::loadPacmanDeathSound() {
  if (!deathBuffer.loadFromFile(deathSoundPath)) {
    std::cerr << "Error loading death sound" << std::endl;
    return false;
  }
  return true;
}

void Entity::playPacmanDeathSound() {
  if (deathSound.getStatus() != sf::Sound::Status::Playing) {
    deathSound.play();
  }
}
// Initialise the game font. Returns true on success; false with an error message on failure.
bool Entity::initGameFont() {
  if (!gameFont.openFromFile(gameFontPath)) {
    std::cerr << "Error loading the game font" << std::endl;
    return false;
  }
  return true;
}

// Draw menu texts (title, Play, Exit) when the game is in MENU or PAUSED state.
void Entity::drawGameFont(sf::RenderWindow &window, GameState &gameState) {
  if (gameState == GameState::MENU || gameState == GameState::PAUSED) {
    window.draw(title);
    window.draw(play);
    window.draw(exit);
  }
}

} // namespace pacman
