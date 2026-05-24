#ifndef GHOST_HPP
#define GHOST_HPP

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

constexpr unsigned int MAX_GHOSTS = 4; // Maximum number of ghosts
namespace pacman {
// Enemy ghost with AI movement. Currently a stub.
// Handles rendering, movement, and collision detection for all ghosts.
class Ghost {
public:
  Ghost();
  ~Ghost();

  // Render all ghosts on the given window
  void drawGhosts(sf::RenderWindow &window);

  // Update ghost positions based on Pacman's position (AI movement)
  void movement(sf::Vector2f pacmanPosition, float deltaTimer, const int FPS);

  // Getters and setters for ghost positions
  sf::Vector2f getGhostsPositions(unsigned int index) const {
    return ghostsPosition[index];
  }
  sf::RectangleShape &getGhostShape(int index) { return ghostsShape[index]; }
  void setGhostsPositions(unsigned int index, sf::Vector2f newPosition) {
    ghostsPosition[index] = newPosition;
  }

  // Check for collision between any ghost and Pacman
  bool ghostsPacmanCollision(sf::CircleShape &pacmanShape);
  bool isValidDirection(int index, Direction dir) const;

  void updateDirection(int index, sf::Vector2f pacmanPos,
                       sf::Vector2f blinkyPos);

private:
  sf::RectangleShape ghostsShape[MAX_GHOSTS]; // Visual representation of ghosts
  Direction ghostsDirection[MAX_GHOSTS];
  static constexpr float GHOST_SPEED = 2.5f;
  const sf::Color ghostsColor[MAX_GHOSTS] = {
      // Colors for each ghost
      sf::Color::Red,           // Ghost 1
      sf::Color(255, 192, 203), // Ghost 2
      sf::Color::Green,         // Ghost 3
      sf::Color(255, 165, 0)    // Ghost 4
  };


  /*
  // Texture-based rendering (currently unused)
  sf::Texture ghostsTexture[MAX_GHOSTS];
  sf::Sprite ghostsSprite;
  */

  std::string ghostsTexturePath; // Path to ghost textures (unused)
  sf::Vector2f ghostsPosition[MAX_GHOSTS] =
      {}; // Current positions of all ghosts
};

} // namespace pacman

#endif // GHOST_HPP
