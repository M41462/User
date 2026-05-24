#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace pacman {

// Tile-based game map (28x31 grid, 32px cells).
// Renders walls, pellets, and power pellets.
// Tile characters:
//   # = wall
//   . = pellet
//   O = power pellet
//   P = Pacman spawn point
//   G = ghost spawn point
class Map {
public:
  Map();
  ~Map();

  // Render the entire map
  void drawMap(sf::RenderWindow &window);

  // Spawn position getters
  const sf::Vector2f getPacmanSpawnPosition();
  std::vector<sf::Vector2f> getGhostsSpawnPositions();

  // Collision detection
  bool isWallCollision(sf::CircleShape &pacmanShape);
  bool isWallCollision(sf::RectangleShape &ghostsShape);
  int checkPelletCollision(
      sf::CircleShape &pacmanShape); // Returns 1 for pellet, 2 for power pellet

  // Game state checks
  bool areAllPelletsEaten() const;

private:
  // Map dimensions and cell size
  static constexpr unsigned int MAP_WIDTH = 28;
  static constexpr unsigned int MAP_HEIGHT = 31;
  static constexpr unsigned int CELL_SIZE = 32;

  // Visual elements
  sf::RectangleShape wall;     // Wall tile
  sf::CircleShape pellet;      // Regular pellet
  sf::CircleShape powerPellet; // Power pellet

  // Visual offsets for centering pellets in cells
  const int pelletOffset = 15;
  const int powerPelletOffset = 10;

  // Map layout - 28x31 grid of tiles
  // clang-format off
  std::vector<std::string> map = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#O####.#####.##.#####.####O#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.#####.##.#####.######",
    "######.#####.##.#####.######",
    "######.##..........##.######",
    "######.##.########.##.######",
    "######.##.########.##.######",
    "#...........GGGG...........#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#......##....##....##......#",
    "######.##.########.##.######",
    "######.##.########.##.######",
    "######.##..........##.######",
    "######.##.########.##.######",
    "######.##.########.##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#O..##................##..O#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##P...##......#",
    "#.########################.#",
    "#..........................#",
    "############################"
  };
  // clang-format on
};

} // namespace pacman

#endif // MAP_HPP
