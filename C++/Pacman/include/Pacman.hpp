#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "Entity.hpp"
#include "GameState.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#define PACMAN_TEXTURES 4

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
  void movement(float deltaTimer, const int FPS, GameState &gamestate);
  const unsigned int getPacmanLives() { return this->lives; }
  void setLives() { this->lives--; }
  bool loadPacmanTextures();

  // Getters and setters
  sf::Sprite &getPacmanShape() { return pacmanShape; }
  sf::Vector2f getPacmanPosition() const { return pacmanPosition; }
  void setPacmanPosition(sf::Vector2f newPosition) {
    pacmanPosition = newPosition;
  }

  sf::RectangleShape getDebugRectangle() const;

private:
  static constexpr float PACMAN_SPEED = 3.0f;
  Direction pacmanDirection;
  sf::Sprite pacmanShape; // Visual representation of Pacman
  sf::Texture pacmanTexture[PACMAN_TEXTURES];
  const std::string pacmanTexturePath[PACMAN_TEXTURES] = {
      "assets/textures/pacman_down.png", "assets/textures/pacman_left.png",
      "assets/textures/pacman_right.png", "assets/textures/pacman_up.png"};
  sf::Vector2f pacmanPosition; // Current position in world coordinates
  static inline unsigned int lives = 3;
};

} // namespace pacman

#endif // PACMAN_HPP
