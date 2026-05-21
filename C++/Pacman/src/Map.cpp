#include "../include/Map.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace pacman {

Map::Map() {
  pellet.setRadius(1);
  powerPellet.setRadius(5);
  pellet.setOutlineThickness(2.f);
  powerPellet.setOutlineThickness(3.f);
  pellet.setOutlineColor(sf::Color::Yellow);
  powerPellet.setOutlineColor(sf::Color::Yellow);
  wall.setFillColor(sf::Color::Blue);
}

Map::~Map() {}

void Map::drawMap(sf::RenderWindow &window) {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      switch (map[i][j]) {
      case '#': { // wall tile - blue rectangle
        wall.setSize({CELL_SIZE, CELL_SIZE});

        wall.setPosition({(static_cast<float>(j * CELL_SIZE)),
                          static_cast<float>(i * CELL_SIZE)});
        window.draw(wall);
        break;
      }
      case '.': { // pellet - small yellow circle
        // +15 offsets centers the 4px-wide circle in the 32px cell
        pellet.setPosition({(static_cast<float>(j * CELL_SIZE + pelletOffset)),
                            static_cast<float>(i * CELL_SIZE + pelletOffset)});
        window.draw(pellet);
        break;
      }

      case 'O': { // power pellet - larger yellow circle
        // +10 offsets centers the 10px-wide circle in the 32px cell
        powerPellet.setPosition(
            {(static_cast<float>(j * CELL_SIZE + powerPelletOffset)),
             static_cast<float>(i * CELL_SIZE + powerPelletOffset)});
        window.draw(powerPellet);
        break;
      }

      case 'G':
        break;

      default:
        break;
      }
    }
  }
}
const sf::Vector2f Map::getSpawnPosition() {
  sf::Vector2f pacmanOffset;
  pacmanOffset.x = 6;
  pacmanOffset.y = 6;

  for (int i = 0; i < MAP_HEIGHT; i++)
    for (int j = 0; j < MAP_WIDTH; j++)
      if (map[i][j] == 'P')
        return {j * CELL_SIZE + pacmanOffset.x, i * CELL_SIZE + pacmanOffset.y};

  return {0.f, 0.f};
}

bool Map::isWallCollision(sf::CircleShape &pacmanShape) {

  sf::FloatRect circleBounds = pacmanShape.getGlobalBounds();
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == '#') {
        sf::Vector2f pos(j * CELL_SIZE, i * CELL_SIZE);
        sf::Vector2f size(CELL_SIZE, CELL_SIZE);
        sf::FloatRect wallBounds(pos, size);
        if (circleBounds.findIntersection(wallBounds))
          return true;
      }
    }
  }
  return false;
}
int Map::checkPelletCollision(sf::CircleShape &pacmanShape) {
  sf::FloatRect bounds = pacmanShape.getGlobalBounds();
  sf::Vector2f center(bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f);
  int col = static_cast<int>(center.x) / CELL_SIZE;
  int row = static_cast<int>(center.y) / CELL_SIZE;
  if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
    return 0;
  char &tile = map[row][col];
  if (tile == '.') {
    tile = ' ';
    return 1;
  } else if (tile == 'O') {
    tile = ' ';
    return 2;
  }
  return 0;
}

bool Map::areAllPelletsEaten() const {
  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      if (map[i][j] == '.' || map[i][j] == 'O')
        return false;
    }
  }
  return true;
}
} // namespace pacman
