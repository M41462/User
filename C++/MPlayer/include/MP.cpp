#include "MP.hpp"
#include "Visual.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

void MPlayer::Draw_Text(sf::RenderWindow &window) {
  text.setFont(font);
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(310, 9));
  text.setString(std::to_string((int)Get_Volume() + 1));
  if (Mute_Music) {
    music->setVolume(0);
    Mute_Text.setString("MUTE");
    Mute_Text.setFont(font);
    Mute_Text.setCharacterSize(30);
    Mute_Text.setFillColor(sf::Color::Red);
    Mute_Text.setPosition(sf::Vector2f(10, 8));
    window.draw(Mute_Text);
  } else {
    Mute_Music = false;
  }
  if (is_running) {
    Play_Text.setString("PLAY");
    Play_Text.setFont(font);
    Play_Text.setCharacterSize(30);
    Play_Text.setFillColor(sf::Color::Green);
    Play_Text.setPosition(sf::Vector2f(600, 10));
    window.draw(Play_Text);
  } else {
    Play_Text.setString("PAUSE");
    Play_Text.setFont(font);
    Play_Text.setCharacterSize(30);
    Play_Text.setFillColor(sf::Color::Green);
    Play_Text.setPosition(sf::Vector2f(600, 10));
    window.draw(Play_Text);
  }
  window.draw(text);
}

void MPlayer::Increase_Volume() {
  float current_volume = music->getVolume();
  music->setVolume(std::min(current_volume + 10, 200.f));
  if (music->getVolume() == 200) {
    std::cout << "Volume : 200%(Max)" << std::endl;
    return;
  }
}
void MPlayer::Decrease_Volume() {
  float current_volume = music->getVolume();
  music->setVolume(std::max(current_volume - 10, 0.f));
  if (music->getVolume() == 0) {
    std::cout << "Volume : 0%(Min)" << std::endl;
    return;
  }
}
void MPlayer::Mute_Volume() {
  if (Mute_Music) {
    music->setVolume(20);
  } else {
    music->setVolume(0);
  }
  Mute_Music = !Mute_Music;
}
std::string MPlayer::Convert_MP4_To_Wave(std::string &filepath) {
  WAV_File = "temp.wav";
  Is_Temp_File = true;
  const std::string command = "ffmpeg -i " + filepath + " " + WAV_File;
  system(command.c_str());
  return WAV_File;
}

float MPlayer::Get_Volume() { return music->getVolume(); }

void MPlayer::Increase_Speed() {
  if (!is_running && Mute_Music)
    return;
  if (current_speed == 0.5f) {
    music->setPitch(1.0f);
    current_speed = 1.0f;
  } else {
    music->setPitch(1.5f);
    current_speed = 1.5f;
  }
}
void MPlayer::Decrease_Speed() {
  if (!is_running && Mute_Music)
    return;
  if (current_speed == 1.5f) {
    music->setPitch(1.0f);
    current_speed = 1.0f;
  } else {
    music->setPitch(0.75f);
    current_speed = 0.5f;
  }
}
bool MPlayer::Init_Music(std::string &musicpath) {
  std::string ext = musicpath.substr(musicpath.find_last_of(".") + 1);

  if (If_File_MP4(musicpath)) {
    musicpath = Convert_MP4_To_Wave(musicpath);
  }

  if (!music->openFromFile(musicpath)) {
    std::cerr << "Failed to load music file: " << musicpath << std::endl;
    return false;
  }
  music->setVolume(20);
  return true;
}

MPlayer::MPlayer()
    : window(nullptr), music(nullptr), is_running(false), current_speed(1.0f) {
  window = new sf::RenderWindow;
  music = new sf::Music;
  std::string *MP4_File;
}

MPlayer::~MPlayer() {
  window->close();
  music->stop();
  delete music;
  delete window;
  if (Is_Temp_File) {
    if (remove(WAV_File.c_str()) == 0) {
      std::cout << "Cleaned up temporary file: " << WAV_File << std::endl;
    } else {
      std::cerr << "Failed to remove temporary file: " << WAV_File << std::endl;
    }
  }
}

void MPlayer::LoadAndPlay(std::string &filepath) {
  if (!Init_Music(filepath)) {
    std::cout << "Error initializing music" << std::endl;
  } else if (If_File_MP4(filepath)) {
    MP4_File = Convert_MP4_To_Wave(filepath);
    LoadAndPlay(MP4_File);
    return;
  }
  current_track = filepath;
  music->play();
  is_running = true;
}

void MPlayer::Run() {
  std::system("clear");
  window->create(sf::VideoMode(700, 600), "MUSIC PLAYER",
                 sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(position);
  window->setFramerateLimit(60);
  Visual.Set_Visual();

  while (window->isOpen() && music->getStatus() != sf::Music::Stopped) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
        break;
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
          Decrease_Speed();
        } else if (event.key.code == sf::Keyboard::Right) {
          Increase_Speed();
        } else if (event.key.code == sf::Keyboard::M) {
          Mute_Volume();
        } else if (event.key.code == sf::Keyboard::Up) {
          Increase_Volume();
        } else if (event.key.code == sf::Keyboard::Down) {
          Decrease_Volume();
        } else if (event.key.code == sf::Keyboard::Space) {
          if (is_running) {
            music->pause();
          } else {
            music->play();
          }
          is_running = !is_running;
        } else if (event.key.code == sf::Keyboard::Escape ||
                   event.key.code == sf::Keyboard::Q) {
          std::cout << "Exiting ..." << std::endl;
          window->close();
        } else if (event.key.code == sf::Keyboard::Enter) {
          music->setVolume(70);
        }
      }
    }

    window->clear(color);

    Visual.Draw_Visual(*window);
    Draw_Text(*window);
    Visual.Update_Visual(*music);

    window->display();
  }
}
