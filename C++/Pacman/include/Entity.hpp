#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameState.hpp"
#include "Utils.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

enum class Direction {DOWN = 0 , LEFT, RIGHT, UP , NONE };

namespace pacman {

// Base entity handling shared setup (window icon, sound effects, etc.).
// Provides common functionality for all game entities.
class Entity {
public:
  Entity();
  virtual ~Entity();

  // Window setup
  void setIconWindow(sf::RenderWindow &window);

  // Menu music
  bool loadMenuMusic();
  void playMenuMusic();

  // Sound effects
  bool loadFoodSound();      // Load regular pellet sound
  void playFoodSound();      // Play regular pellet sound
  bool loadPowerFoodSound(); // Load power pellet sound
  void playPowerFoodSound(); // Play power pellet sound
  bool loadPacmanDeathSound();
  void playPacmanDeathSound();
  bool initGameFont();
  void drawGameFont(sf::RenderWindow &window, GameState &gameState,
                    Utils &utils, bool &running);

private:
  sf::Image icon;                 // Window icon
  sf::Music startMusic;           // Background music
  sf::SoundBuffer eatBuffer;      // Buffer for pellet sound
  sf::Sound foodSound;            // Sound for pellet collection
  sf::SoundBuffer powerEatBuffer; // Buffer for power pellet sound
  sf::Sound powerFoodSound;       // Sound for power pellet collection
  sf::SoundBuffer deathBuffer;
  sf::Sound deathSound; // Sound for pacman death;
  sf::Font gameFont;
  sf::Text title;
  sf::Text play;
  sf::Text exit;
  sf::Text texts[MAX_TEXT] = {title, play, exit};

  // File paths for audio assets
  // Audio asset file paths
  const std::string menuMusicPath = "assets/sounds/start_music.wav";
  const std::string eatPelletPath = "assets/sounds/pacman_chomp.wav";
  const std::string eatPowerPelletPath = "assets/sounds/pacman_eatfruit.wav";
  const std::string deathSoundPath = "assets/sounds/pacman_death.wav";
  const std::string gameFontPath = "assets/fonts/pac-font.ttf";
};

} // namespace pacman

#endif // ENTITY_HPP
