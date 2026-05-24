#include "../include/Pacman.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowBase.hpp>

namespace pacman {

// Initializes Pacman's visual appearance
Pacman::Pacman() : pacmanShape(sf::Sprite(pacmanTexture[0])) {
  pacmanDirection = Direction::RIGHT;
}

Pacman::~Pacman() {}

// Renders Pacman on the given window
void Pacman::drawPacman(sf::RenderWindow &window) {
  pacmanShape.setPosition(pacmanPosition);
  static int currentIndex = 2; 
  switch (pacmanDirection) {
    case Direction::DOWN:
      currentIndex = 0; 
      break;
    case Direction::LEFT:
      currentIndex = 1; 
      break;
    case Direction::RIGHT:
      currentIndex = 2; 
      break;
    case Direction::UP:
      currentIndex = 3; 
      break;
    case Direction::NONE:
    default:
      break;
  }

  pacmanShape.setTexture(pacmanTexture[currentIndex]);
  window.draw(pacmanShape);
}

sf::RectangleShape Pacman::getDebugRectangle() const {
  // Get the actual size of the sprite after scaling
  sf::FloatRect bounds = pacmanShape.getGlobalBounds();

  // Create a rectangle with the same size as Pacman's texture
  sf::RectangleShape rect(sf::Vector2f(bounds.size.x, bounds.size.y));

  // Position it at Pacman's location
  rect.setPosition({bounds.position.x, bounds.position.y});

  // Make it visible for debugging
  rect.setFillColor(sf::Color::Transparent);
  rect.setOutlineColor(sf::Color::Red);
  rect.setOutlineThickness(2.0f);

  return rect;
}

bool Pacman::loadPacmanTextures() {
  for (int i = 0; i < PACMAN_TEXTURES; i++) {
    if (!pacmanTexture[i].loadFromFile(pacmanTexturePath[i]))
      throw std::runtime_error("Failed to load " + pacmanTexturePath[i]);
  }

  pacmanShape.setScale(sf::Vector2f(0.90f, 0.90f));
  pacmanShape.setTextureRect(
      sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(26, 26)));
  pacmanShape.setTexture(pacmanTexture[2]);
  return true;
}

// Handles keyboard input and updates Pacman's position
// Movement speed is scaled by FPS and delta time for smooth, frame-independent
// motion
void Pacman::movement(float deltaTimer, const int FPS, GameState &gameState) {
  if (gameState != GameState::PLAYING)
    return;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
    pacmanPosition.y -= PACMAN_SPEED * FPS * deltaTimer; // Move up
    pacmanDirection = Direction::UP;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
    pacmanPosition.y += PACMAN_SPEED * FPS * deltaTimer; // Move down
    pacmanDirection = Direction::DOWN;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
    pacmanPosition.x -= PACMAN_SPEED * FPS * deltaTimer; // Move left
    pacmanDirection = Direction::LEFT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
    pacmanPosition.x += PACMAN_SPEED * FPS * deltaTimer; // Move right
    pacmanDirection = Direction::RIGHT;
  }
  else{
    pacmanDirection = Direction::NONE; 
  }
  pacmanShape.setPosition(pacmanPosition);
}

// Checks if a single wall rectangle overlaps with the Pacman circle shape.
// Unused — wall collision is handled tile-wide in Map::isWallCollision.
bool isWallCollision(sf::CircleShape &pacmanShape, sf::RectangleShape &wall) {
  // Get wall corners
  sf::Vector2f topLeft = wall.getPosition();
  sf::Vector2f topRight = topLeft + sf::Vector2f(wall.getSize().x, 0);
  sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0, wall.getSize().y);
  sf::Vector2f bottomRight = topLeft + wall.getSize();

  // Calculate squared radius for distance comparison
  float radiusSq = pacmanShape.getRadius() * pacmanShape.getRadius();
  sf::Vector2f center = pacmanShape.getPosition();

  // Lambda to check if a point is inside Pacman's circle
  auto isInside = [&](sf::Vector2f p) {
    float dx = p.x - center.x;
    float dy = p.y - center.y;
    return (dx * dx + dy * dy) <= radiusSq;
  };

  // Check if any wall corner is inside Pacman
  if (isInside(topLeft) || isInside(topRight) || isInside(bottomLeft) ||
      isInside(bottomRight)) {
    return true;
  }

  // Check if Pacman's center is inside the wall
  sf::FloatRect rectBounds = wall.getGlobalBounds();
  return rectBounds.contains(center);
}
} // namespace pacman
