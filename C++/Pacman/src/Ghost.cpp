#include "../include/Ghost.hpp"
#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>

namespace pacman {

// Initializes ghost visual appearance and positions
Ghost::Ghost()
    : ghostsShape{sf::Sprite(ghostsTexture[0]), sf::Sprite(ghostsTexture[1]),
                  sf::Sprite(ghostsTexture[2]), sf::Sprite(ghostsTexture[3])} {
  const sf::Vector2f size(23.f, 23.f); // Ghost size
}
Ghost::~Ghost() {}

void Ghost::initGhosts() {
  Direction displayDirs[MAX_GHOSTS] = {
      Direction::DOWN, Direction::LEFT, Direction::RIGHT, Direction::UP};
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (!ghostsTexture[i].loadFromFile(ghostsTexturePath[i])) {
      throw std::runtime_error("Error Init ghosts texture");
    }
    ghostsShape[i].setTexture(ghostsTexture[i]);
    ghostsShape[i].setTextureRect(
        sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(24, 24)));
    ghostsShape[i].setPosition(ghostsPosition[i]);
    ghostsDirection[i] = Direction::NONE;
  }
}

// Renders all ghosts on the given window
void Ghost::drawGhosts(sf::RenderWindow &window) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghostsShape[i].setPosition(ghostsPosition[i]);
    window.draw(ghostsShape[i]);
  }
}

// Checks for collision between any ghost and Pacman
bool Ghost::ghostsPacmanCollision(sf::Sprite &pacmanShape) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (pacmanShape.getGlobalBounds().findIntersection(
            ghostsShape[i].getGlobalBounds())) {
      return true; // Collision detected
    }
  }
  return false; // No collision
}

// Updates ghost positions based on Pacman's position (AI movement)
// Currently a stub - no actual movement logic implemented
void Ghost::movement(sf::Vector2f pacmanPosition, float deltaTimer,
                     const int FPS) {
  // TODO: Implement ghost AI and movement patterns
  for (int i = 0; i < MAX_GHOSTS; i++) {
    switch (ghostsDirection[i]) {
    case Direction::UP:
      ghostsPosition[i].y -= GHOST_SPEED * FPS * deltaTimer;
      break;

    case Direction::DOWN:
      ghostsPosition[i].y += GHOST_SPEED * FPS * deltaTimer;
      break;

    case Direction::LEFT:
      ghostsPosition[i].x -= GHOST_SPEED * FPS * deltaTimer;
      break;

    case Direction::RIGHT:
      ghostsPosition[i].x += GHOST_SPEED * FPS * deltaTimer;
      break;
    default:
      break;
    }
  }
}

void Ghost::updateDirection(int index, sf::Vector2f pacmanPos,
                            sf::Vector2f blinkyPos) {}

} // namespace pacman
