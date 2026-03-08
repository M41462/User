#pragma once
#include "Visual.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <cstring>
class MPlayer {
public:
  MPlayer();
  ~MPlayer();
  void Run();
  bool Init_Music(std::string &musicpath);
  bool If_File_MP4(const std::string &filepath) {
    if (strstr(filepath.c_str(), ".mp4") != NULL) {
      return true;
    }
    return false;
  }
  std::string Convert_MP4_To_Wave(std::string &filepath);
  void LoadAndPlay(std::string &filepath);
  void Increase_Volume();
  void Decrease_Volume();
  void Increase_Speed();
  void Decrease_Speed();
  void Mute_Volume();
  float Get_Volume();

private:
  sf::Font font;
  sf::Text text;
  sf::Text Mute_Text;
  sf::Text Play_Text;
  void Draw_Text(sf::RenderWindow &window);
  void Set_Font();
  Visual Visual;
  const sf::Vector2i position = {350, 100};
  const sf::Color color = {20, 20, 30};
  std::string current_track;
  sf::RenderWindow *window;
  sf::Music *music;
  bool is_running = false;
  bool Mute_Music = false;
  float current_speed = 1.0f;
  std::string MP4_File;
  std::string WAV_File;
  bool Is_Temp_File = false;
};
