#ifndef GHOST_HPP
#define GHOST_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

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
  void setGhostsPositions(unsigned int index, sf::Vector2f newPosition) {
    ghostsPosition[index] = newPosition;
  }

  // Check for collision between any ghost and Pacman
  bool ghostsPacmanCollision(sf::CircleShape &pacmanShape);

private:
  static constexpr unsigned int MAX_GHOSTS = 4; // Maximum number of ghosts

  sf::RectangleShape ghostsShape[MAX_GHOSTS]; // Visual representation of ghosts
  const sf::Color ghostsColor[MAX_GHOSTS] = {
      // Colors for each ghost
      sf::Color::Blue,  // Ghost 1
      sf::Color::Red,   // Ghost 2
      sf::Color::Green, // Ghost 3
      sf::Color::Yellow // Ghost 4
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
