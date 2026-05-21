#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace pacman {

// Base entity handling shared setup (window icon, etc.).
class Entity {
public:
  Entity();
  virtual ~Entity();
  void setIconWindow(sf::RenderWindow &window);
  bool loadMenuMusic();
  void playMenuMusic();
  bool loadFoodSound();
  void playFoodSound();
  bool loadPowerFoodSound();
  void playPowerFoodSound();

private:
  sf::Image icon;
  sf::Music startMusic;
  sf::SoundBuffer eatBuffer;
  sf::Sound foodSound;
  sf::SoundBuffer powerEatBuffer;
  sf::Sound powerFoodSound;

  const std::string menuMusicPath = "assets/sounds/start_music.wav";
  const std::string eatPelletPath = "assets/sounds/pacman_chomp.wav";
  const std::string eatPowerPelletPath = "assets/sounds/pacman_eatfruit.wav";
};

} // namespace pacman

#endif // ENTITY_HPP
