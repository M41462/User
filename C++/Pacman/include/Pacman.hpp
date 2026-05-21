#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
namespace pacman {

// Player-controlled Pac-Man character with keyboard movement.
class Pacman {
public:
  Pacman();
  ~Pacman();

  void drawPacman(sf::RenderWindow &window);
  void movement(float deltaTimer, const int FPS);

  sf::CircleShape &getPacmanShape() { return this->pacmanShape; }
  sf::Vector2f getPacmanPosition() { return pacmanPosition; }
  void setPacmanPosition(sf::Vector2f newPosition) { this->pacmanPosition = newPosition; }

private:
  sf::CircleShape pacmanShape;
  sf::Vector2f pacmanPosition;
};

} // namespace pacman

#endif // PACMAN_HPP
