#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace pacman {

// Player-controlled Pac-Man character with keyboard movement.
// Handles rendering, movement, and position management.
class Pacman {
public:
  Pacman();
  ~Pacman();

  // Render Pacman on the given window
  void drawPacman(sf::RenderWindow &window);

  // Handle keyboard input and update position
  void movement(float deltaTimer, const int FPS);
  const unsigned int getPacmanLives() { return this->lives; }
  void setLives() { this->lives--; }

  // Getters and setters
  sf::CircleShape &getPacmanShape() { return pacmanShape; }
  sf::Vector2f getPacmanPosition() const { return pacmanPosition; }
  void setPacmanPosition(sf::Vector2f newPosition) {
    pacmanPosition = newPosition;
  }

private:
  sf::CircleShape pacmanShape; // Visual representation of Pacman
  sf::Vector2f pacmanPosition; // Current position in world coordinates
  static inline unsigned int lives = 3;
};

} // namespace pacman

#endif // PACMAN_HPP
