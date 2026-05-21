#include "../include/Pacman.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace pacman {

Pacman::Pacman() {
  pacmanShape.setRadius(10.f);
  pacmanShape.setOutlineThickness(2.f);
  pacmanShape.setFillColor(sf::Color::Red);
}

Pacman::~Pacman() {}

void Pacman::drawPacman(sf::RenderWindow &window) {
  pacmanShape.setPosition(pacmanPosition);
  window.draw(pacmanShape);
}

void Pacman::movement(float deltaTimer, const int FPS) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
    pacmanPosition.y -= 3 * FPS * deltaTimer;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
    pacmanPosition.y += 3 * FPS * deltaTimer;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
    pacmanPosition.x -= 3 * FPS * deltaTimer;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
    pacmanPosition.x += 3 * FPS * deltaTimer;
  }
  pacmanShape.setPosition(pacmanPosition);
}

// Checks if a single wall rectangle overlaps with the Pacman circle shape.
// Unused — wall collision is handled tile-wide in Map::isWallCollision.
bool isWallCollision(sf::CircleShape &pacmanShape, sf::RectangleShape &wall) {

  sf::Vector2f topLeft = wall.getPosition();
  sf::Vector2f topRight = topLeft + sf::Vector2f(wall.getSize().x, 0);
  sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0, wall.getSize().y);
  sf::Vector2f bottomRight = topLeft + wall.getSize();

  float radiusSq = pacmanShape.getRadius() * pacmanShape.getRadius();
  sf::Vector2f center = pacmanShape.getPosition();

  auto isInside = [&](sf::Vector2f p) {
    float dx = p.x - center.x;
    float dy = p.y - center.y;
    return (dx * dx + dy * dy) <= radiusSq;
  };

  if (isInside(topLeft) || isInside(topRight) || isInside(bottomLeft) ||
      isInside(bottomRight)) {
    return true;
  }

  sf::FloatRect rectBounds = wall.getGlobalBounds();
  return rectBounds.contains(center);
}
} // namespace pacman
