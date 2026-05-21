#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
namespace pacman {

// Tile-based game map (28x31 grid, 32px cells). Renders walls, pellets,
// power pellets. Tile chars: #=wall .=pellet O=power pellet P=spawn G=ghost.
class Map {
public:
  Map();
  ~Map();
  void drawMap(sf::RenderWindow &window);
  const sf::Vector2f getSpawnPosition();
  bool isWallCollision(sf::CircleShape &pacmanShape);
  int checkPelletCollision(sf::CircleShape &pacmanShape);
  bool areAllPelletsEaten() const;

private:
  static constexpr unsigned int MAP_WIDTH = 28;
  static constexpr unsigned int MAP_HEIGHT = 31;
  static constexpr unsigned int CELL_SIZE = 32;

  sf::RectangleShape wall;
  sf::CircleShape pellet;
  sf::CircleShape powerPellet;

  const int pelletOffset = 15;
  const int powerPelletOffset = 10;
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
};

} // namespace pacman

#endif // MAP_HPP
