#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>

#include "MP.hpp"

#include "Visual.hpp"

namespace {
constexpr float VOLUME_STEP = 10.0f;
constexpr float MAX_VOLUME = 200.0f;
constexpr float MIN_VOLUME = 0.0f;
constexpr float DEFAULT_VOLUME = 20.0f;
constexpr float SPEED_NORMAL = 1.0f;
constexpr float SPEED_FAST = 1.5f;
constexpr float SPEED_SLOW = 0.5f;
} // namespace

void MPlayer::setupTextStyle(sf::Text &txt, const std::string &str,
                             sf::Color color, float x, float y) {
  txt.setFont(font);
  txt.setCharacterSize(30);
  txt.setFillColor(color);
  txt.setPosition(sf::Vector2f(x, y));
  txt.setString(str);
}

void MPlayer::drawText(sf::RenderWindow &window) {
  text.setFont(font);
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(310.0f, 9.0f));
  text.setString(std::to_string(static_cast<int>(Get_Volume() + 1)));

  if (muteMusic) {
    muteText.setFont(font);
    muteText.setCharacterSize(30);
    muteText.setFillColor(sf::Color::Red);
    muteText.setPosition(sf::Vector2f(10.0f, 8.0f));
    muteText.setString("MUTE");
    window.draw(muteText);
  }

  if (isRunning) {
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::Green);
    playText.setPosition(sf::Vector2f(600.0f, 10.0f));
    playText.setString("PLAY");
    window.draw(playText);
  } else {
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::Green);
    playText.setPosition(sf::Vector2f(600.0f, 10.0f));
    playText.setString("PAUSE");
    window.draw(playText);
  }

  window.draw(text);
}

void MPlayer::Increase_Volume() {
  const float currentVolume = music->getVolume();
  const float newVolume = std::min(currentVolume + VOLUME_STEP, MAX_VOLUME);
  music->setVolume(newVolume);

  if (music->getVolume() >= MAX_VOLUME) {
    std::cout << "Volume : 200%(Max)" << std::endl;
  }
}

void MPlayer::Decrease_Volume() {
  const float currentVolume = music->getVolume();
  const float newVolume = std::max(currentVolume - VOLUME_STEP, MIN_VOLUME);
  music->setVolume(newVolume);

  if (music->getVolume() <= MIN_VOLUME) {
    std::cout << "Volume : 0%(Min)" << std::endl;
  }
}

void MPlayer::Mute_Volume() {
  if (muteMusic) {
    music->setVolume(DEFAULT_VOLUME);
  } else {
    music->setVolume(MIN_VOLUME);
  }
  muteMusic = !muteMusic;
}

std::string MPlayer::Convert_MP4_To_Wave(std::string &filepath) {
  wavFile = "temp.wav";
  isTempFile = true;
  const std::string command = "ffmpeg -i \"" + filepath + "\" " + wavFile;
  const int result = std::system(command.c_str());
  if (result != 0) {
    std::cerr << "Warning: ffmpeg conversion returned non-zero: " << result
              << std::endl;
  }
  return wavFile;
}

float MPlayer::Get_Volume() { return music->getVolume(); }

void MPlayer::Increase_Speed() {
  if (!isRunning && muteMusic) {
    return;
  }

  if (currentSpeed == SPEED_SLOW) {
    music->setPitch(SPEED_NORMAL);
    currentSpeed = SPEED_NORMAL;
  } else {
    music->setPitch(SPEED_FAST);
    currentSpeed = SPEED_FAST;
  }
}

void MPlayer::Decrease_Speed() {
  if (!isRunning && muteMusic) {
    return;
  }

  if (currentSpeed == SPEED_FAST) {
    music->setPitch(SPEED_NORMAL);
    currentSpeed = SPEED_NORMAL;
  } else {
    music->setPitch(SPEED_SLOW);
    currentSpeed = SPEED_SLOW;
  }
}

bool MPlayer::Init_Music(std::string &musicpath) {
  if (If_File_MP4(musicpath)) {
    musicpath = Convert_MP4_To_Wave(musicpath);
  }

  if (!music->openFromFile(musicpath)) {
    std::cerr << "Failed to load music file: " << musicpath << std::endl;
    return false;
  }
  music->setVolume(DEFAULT_VOLUME);
  return true;
}

MPlayer::MPlayer()
    : window(nullptr), music(nullptr), isRunning(false),
      currentSpeed(SPEED_NORMAL) {
  window = new sf::RenderWindow;
  music = new sf::Music;
}

MPlayer::~MPlayer() {
  if (window) {
    window->close();
    delete window;
  }
  if (music) {
    music->stop();
    delete music;
  }

  if (isTempFile && !wavFile.empty()) {
    if (std::remove(wavFile.c_str()) == 0) {
      std::cout << "Cleaned up temporary file: " << wavFile << std::endl;
    } else {
      std::cerr << "Failed to remove temporary file: " << wavFile << std::endl;
    }
  }
}

void MPlayer::LoadAndPlay(std::string &filepath) {
  if (!Init_Music(filepath)) {
    std::cerr << "Error initializing music" << std::endl;
    return;
  }

  if (If_File_MP4(filepath)) {
    mp4File = Convert_MP4_To_Wave(filepath);
    LoadAndPlay(mp4File);
    return;
  }

  currentTrack = filepath;
  music->play();
  isRunning = true;
}

void MPlayer::Run() {
  std::system("clear");

  window->create(sf::VideoMode(700, 600), "MUSIC PLAYER",
                 sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(windowPosition);
  window->setFramerateLimit(60);
  visual.Set_Visual();

  while (window->isOpen() && music->getStatus() != sf::Music::Stopped) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
        break;
      }
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Left:
          Decrease_Speed();
          break;
        case sf::Keyboard::Right:
          Increase_Speed();
          break;
        case sf::Keyboard::M:
          Mute_Volume();
          break;
        case sf::Keyboard::Up:
          Increase_Volume();
          break;
        case sf::Keyboard::Down:
          Decrease_Volume();
          break;
        case sf::Keyboard::Space:
          if (isRunning) {
            music->pause();
          } else {
            music->play();
          }
          isRunning = !isRunning;
          break;
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
          std::cout << "Exiting ..." << std::endl;
          window->close();
          break;
        case sf::Keyboard::Enter:
          music->setVolume(70.0f);
          break;
        default:
          break;
        }
      }
    }

    window->clear(backgroundColor);
    visual.Draw_Visual(*window);
    drawText(*window);
    visual.Update_Visual(*music);
    window->display();
  }
}
