# Ghost Texture Rendering Guide

## The Problem
The ghost PNGs are spritesheets (288×24 = 12 frames of 24×24).
SFML draws the ENTIRE image unless you crop it with `setTextureRect()`.

## The Fix — Two changes in `src/Ghost.cpp`

### 1. initGhosts() — Crop to one frame + set direction
```cpp
void Ghost::initGhosts() {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (!ghostsTexture[i].loadFromFile(ghostsTexturePath[i])) {
      throw std::runtime_error("Error Init ghosts texture");
    }
    ghostsShape[i].setTexture(ghostsTexture[i]);
    ghostsShape[i].setTextureRect(
        sf::IntRect(sf::Vector2i(0, 0),
                    sf::Vector2i(24, 24)));     // <-- crop to first 24x24 frame
    ghostsShape[i].setPosition(ghostsPosition[i]);
    ghostsDirection[i] = Direction::UP;          // <-- initialize direction
  }
}
```

### 2. drawGhosts() — Animate by direction
```cpp
void Ghost::drawGhosts(sf::RenderWindow &window) {
  static float animTimer = 0;
  animTimer += 0.15f;
  int animFrame = static_cast<int>(animTimer) % 2;

  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghostsShape[i].setPosition(ghostsPosition[i]);
    int dirIndex = static_cast<int>(ghostsDirection[i]);
    int frameX = (dirIndex * 2 + animFrame) * 24;
    ghostsShape[i].setTextureRect(
        sf::IntRect(sf::Vector2i(frameX, 0),
                    sf::Vector2i(24, 24)));      // <-- pick frame by direction
    window.draw(ghostsShape[i]);                 // <-- THIS draws it
  }
}
```

### Frame layout (spritesheet: 12 frames × 24px)

| Direction | Enum | Frames |
|-----------|------|--------|
| DOWN      | 0    | 0, 1   |
| LEFT      | 1    | 2, 3   |
| RIGHT     | 2    | 4, 5   |
| UP        | 3    | 6, 7   |

### Also needed in `include/Ghost.hpp`
Add this constant in the `private:` section:
```cpp
static constexpr int GHOST_FRAME_SIZE = 24;
```
