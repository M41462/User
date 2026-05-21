#include "../include/Entity.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

namespace pacman {

// Initializes sound volumes and buffers
Entity::Entity() : foodSound(eatBuffer), powerFoodSound(powerEatBuffer) {
  startMusic.setVolume(30.f); // Background music volume
  foodSound.setVolume(30.f);  // Sound effect volume
}

Entity::~Entity() {}

// Sets the window icon from file
void Entity::setIconWindow(sf::RenderWindow &window) {
  if (icon.loadFromFile("assets/game.png")) {
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
  } else {
    std::cerr << "Error loading window icon" << std::endl;
  }
}

// Loads menu background music
bool Entity::loadMenuMusic() {
  if (!startMusic.openFromFile(menuMusicPath.c_str())) {
    std::cerr << "Error playing music" << std::endl;
    return false;
  }
  return true;
}

// Plays menu background music
void Entity::playMenuMusic() { startMusic.play(); }

// Loads sound effect for regular pellet collection
bool Entity::loadFoodSound() {
  if (!eatBuffer.loadFromFile(eatPelletPath)) {
    std::cerr << "Error loading food sound" << std::endl;
    return false;
  }
  return true;
}

// Loads sound effect for power pellet collection
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

} // namespace pacman
