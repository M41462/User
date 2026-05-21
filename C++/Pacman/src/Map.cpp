#include "../include/Map.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace pacman {

// Initializes map visual elements (walls, pellets, power pellets)
Map::Map() {
  pellet.setRadius(1);                       // Small pellet
  powerPellet.setRadius(5);                  // Larger power pellet
  pellet.setOutlineThickness(2.f);           // Pellet outline thickness
  powerPellet.setOutlineThickness(3.f);      // Power pellet outline thickness
  pellet.setOutlineColor(sf::Color::Yellow); // Pellet color
  powerPellet.setOutlineColor(sf::Color::Yellow); // Power pellet color
  wall.setFillColor(sf::Color::Blue);             // Wall color
}

Map::~Map() {}

// Renders the entire map (walls, pellets, power pellets)
void Map::drawMap(sf::RenderWindow &window) {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      switch (map[i][j]) {
      case '#': { // Wall tile - blue rectangle
        wall.setSize({CELL_SIZE, CELL_SIZE});
        wall.setPosition({static_cast<float>(j * CELL_SIZE),
                          static_cast<float>(i * CELL_SIZE)});
        window.draw(wall);
        break;
      }
      case '.': { // Pellet - small yellow circle
        // +15 offsets centers the 4px-wide circle in the 32px cell
        pellet.setPosition({static_cast<float>(j * CELL_SIZE + pelletOffset),
                            static_cast<float>(i * CELL_SIZE + pelletOffset)});
        window.draw(pellet);
        break;
      }
      case 'O': { // Power pellet - larger yellow circle
        // +10 offsets centers the 10px-wide circle in the 32px cell
        powerPellet.setPosition(
            {static_cast<float>(j * CELL_SIZE + powerPelletOffset),
             static_cast<float>(i * CELL_SIZE + powerPelletOffset)});
        window.draw(powerPellet);
        break;
      }
      case 'G': // Ghost spawn point - no visual representation
        break;
      default: // Empty space or other tiles
        break;
      }
    }
  }
}

// Finds and returns Pacman's spawn position on the map
const sf::Vector2f Map::getPacmanSpawnPosition() {
  sf::Vector2f pacmanOffset(5.f, 5.f); // Offset to center Pacman in cell

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == 'P') {
        return {j * CELL_SIZE + pacmanOffset.x, i * CELL_SIZE + pacmanOffset.y};
      }
    }
  }

  return {0.f, 0.f}; // Fallback position if spawn not found
}

// Finds and returns all ghost spawn positions on the map
std::vector<sf::Vector2f> Map::getGhostsSpawnPositions() {
  sf::Vector2f ghostsOffset(5.f, 5.f); // Offset to center ghosts in cell
  std::vector<sf::Vector2f> positions;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == 'G') {
        positions.push_back(
            {j * CELL_SIZE + ghostsOffset.x, i * CELL_SIZE + ghostsOffset.y});
      }
    }
  }
  return positions;
}

// Checks if Pacman is colliding with any wall
bool Map::isWallCollision(sf::CircleShape &pacmanShape) {
  sf::FloatRect circleBounds = pacmanShape.getGlobalBounds();

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == '#') { // Wall tile
        sf::Vector2f pos(j * CELL_SIZE, i * CELL_SIZE);
        sf::Vector2f size(CELL_SIZE, CELL_SIZE);
        sf::FloatRect wallBounds(pos, size);
        if (circleBounds.findIntersection(wallBounds)) {
          return true;
        }
      }
    }
  }
  return false;
}

// Checks if Pacman is colliding with any pellet or power pellet
// Returns 1 for regular pellet, 2 for power pellet, 0 for no collision
int Map::checkPelletCollision(sf::CircleShape &pacmanShape) {
  sf::FloatRect bounds = pacmanShape.getGlobalBounds();
  sf::Vector2f center(bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f);

  // Convert world position to grid coordinates
  int col = static_cast<int>(center.x) / CELL_SIZE;
  int row = static_cast<int>(center.y) / CELL_SIZE;

  // Check if position is within map bounds
  if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH) {
    return 0;
  }

  char &tile = map[row][col];
  if (tile == '.') { // Regular pellet
    tile = ' ';      // Remove pellet from map
    return 1;
  } else if (tile == 'O') { // Power pellet
    tile = ' ';             // Remove power pellet from map
    return 2;
  }

  return 0; // No collision
}

// Checks if all pellets and power pellets have been eaten
bool Map::areAllPelletsEaten() const {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == '.' || map[i][j] == 'O') {
        return false; // Found uneaten pellet
      }
    }
  }
  return true; // All pellets eaten
}

} // namespace pacman
