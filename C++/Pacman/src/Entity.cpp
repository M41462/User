#include "../include/Entity.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

namespace pacman {

Entity::Entity() : foodSound(eatBuffer), powerFoodSound(powerEatBuffer) {
  startMusic.setVolume(30.f);
  foodSound.setVolume(30.f);
}

Entity::~Entity() {}

void Entity::setIconWindow(sf::RenderWindow &window) {
  if (icon.loadFromFile("assets/game.png")) {
    window.setIcon(icon.getSize(), icon.getPixelsPtr());
  } else {
    std::cerr << "Error loading window icon" << std::endl;
    return;
  }
}

bool Entity::loadMenuMusic() {
  if (!startMusic.openFromFile(menuMusicPath.c_str())) {
    std::cerr << "Error playing music" << std::endl;
    return false;
  }
  return true;
}

void Entity::playMenuMusic() { startMusic.play(); }

bool Entity::loadFoodSound() {
  if (!eatBuffer.loadFromFile(eatPelletPath)) {
    std::cerr << "Error loading food sound" << std::endl;
    return false;
  }
  return true;
}
bool Entity::loadPowerFoodSound() {
  if (!powerEatBuffer.loadFromFile(eatPowerPelletPath)) {
    std::cerr << "Error loading power pellet sound" << std::endl;
    return false;
  }
  return true;
}
void Entity::playFoodSound() {
  if (foodSound.getStatus() != sf::Sound::Status::Playing)
    foodSound.play();
}
void Entity::playPowerFoodSound() {
  if (powerFoodSound.getStatus() != sf::Sound::Status::Playing)
    powerFoodSound.play();
}

} // namespace pacman
