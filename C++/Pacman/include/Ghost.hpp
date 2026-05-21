#ifndef GHOST_HPP
#define GHOST_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
namespace pacman {

// Enemy ghost with AI movement. Currently a stub.
class Ghost {
public:
  Ghost();
  ~Ghost();
  bool initGhostsTexture(); 
  void drawGhosts(); 

private:
  static constexpr unsigned int MAX_GHOSTS = 4; 
  sf::Texture ghostsTexture[MAX_GHOSTS]; 
  sf::Sprite ghostsSprite; 
  std::string ghostsTexturePath;
  sf::Vector2f ghostsPosition; 


};

} // namespace pacman

#endif // GHOST_HPP
