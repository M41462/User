#include "../include/Ghost.hpp"
#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace pacman {

// Initializes ghost visual appearance and positions
Ghost::Ghost() {
  const sf::Vector2f size(23.f, 23.f); // Ghost size
  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghostsShape[i].setSize(size);
    ghostsShape[i].setFillColor(ghostsColor[i]); // Set individual colors
    ghostsShape[i].setPosition(ghostsPosition[i]);
  }
}

Ghost::~Ghost() {}

// Renders all ghosts on the given window
void Ghost::drawGhosts(sf::RenderWindow &window) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghostsShape[i].setPosition(ghostsPosition[i]);
    window.draw(ghostsShape[i]);
  }
}

// Checks for collision between any ghost and Pacman
bool Ghost::ghostsPacmanCollision(sf::CircleShape &pacmanShape) {
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
    case Direction::NONE:
    default:
      break;
    }
  }
}

void Ghost::updateDirection(int index, sf::Vector2f pacmanPos,
                            sf::Vector2f blinkyPos) {}

} // namespace pacman
