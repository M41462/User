#include "../include/Entity.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <stdexcept>

namespace pacman {

// Constructor – initialise audio buffers, set default volumes, enable font
// smoothing, and configure menu text.
Entity::Entity()
    : foodSound(eatBuffer), powerFoodSound(powerEatBuffer),
      deathSound(deathBuffer), title(gameFont), play(gameFont), exit(gameFont) {
  startMusic.setVolume(30.f); // Background music volume
  foodSound.setVolume(30.f);  // Sound effect volume
  gameFont.setSmooth(true);

  title.setPosition({330.f, 150.f});
  play.setPosition({370.f, 350.f});
  exit.setPosition({370.f, 550.f});

  title.setString("PACMAN");
  play.setString("Play");
  exit.setString("Exit");
  title.setFillColor(sf::Color::Green);
  texts[0].setString("PACMAN");
  texts[1].setString("Play");
  texts[2].setString("Exit");
  texts[0].setPosition({330.f, 150.f});
  texts[1].setPosition({370.f, 350.f});
  texts[2].setPosition({370.f, 550.f});
  for (auto &t : texts)
    t.setCharacterSize(40);
}

// Destructor: SFML resources (fonts, sounds, textures) are RAII-managed and
// released automatically.
Entity::~Entity() {}

// Load and set the window icon from assets/game.png (error logged if missing).
void Entity::setIconWindow(sf::RenderWindow &window) {
  if (!icon.loadFromFile("assets/logo/game.png"))
    throw std::runtime_error("Failed to load window icon: assets/game.png");
  window.setIcon(icon.getSize(), icon.getPixelsPtr());
}

// Load menu background music; returns false and logs an error on failure.
bool Entity::loadMenuMusic() {
  if (!startMusic.openFromFile(menuMusicPath.c_str())) {
    throw std::runtime_error("Error playing music");
  }
  return true;
}

// Plays menu background music
void Entity::playMenuMusic() { startMusic.play(); }

// Load sound for regular pellets; logs error on failure.
bool Entity::loadFoodSound() {
  if (!eatBuffer.loadFromFile(eatPelletPath)) {
    throw std::runtime_error("Error loading pellet sound");
  }
  return true;
}

// Load sound for power pellets; logs error on failure.
bool Entity::loadPowerFoodSound() {
  if (!powerEatBuffer.loadFromFile(eatPowerPelletPath)) {
    throw std::runtime_error("Error loading power pellet sound");
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
    throw std::runtime_error("Error loading death sound");
  }
  return true;
}

void Entity::playPacmanDeathSound() {
  if (deathSound.getStatus() != sf::Sound::Status::Playing) {
    deathSound.play();
  }
}
// Initialise the game font. Returns true on success; false with an error
// message on failure.
bool Entity::initGameFont() {
  if (!gameFont.openFromFile(gameFontPath)) {
    throw std::runtime_error("Error loading the game font");
  }
  return true;
}

// Draw menu texts (title, Play, Exit) when the game is in MENU or PAUSED state.
void Entity::drawGameFont(sf::RenderWindow &window, GameState &gameState,
                          Utils &utils, bool &running) {
  utils.choseOptions(window, gameState, running, texts);
}

} // namespace pacman
