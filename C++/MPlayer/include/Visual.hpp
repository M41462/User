#ifndef VISUAL_HPP
#define VISUAL_HPP
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <cmath>
const int WIDTH = 700;
const int HEIGHT = 600;
const int BAR_COUNT = 128;

class Visual {
public:
  void Set_Visual();
  void Update_Visual(sf::Music &music);
  void Draw_Visual(sf::RenderWindow &window);

private:
  sf::RectangleShape Bars[BAR_COUNT];
  sf::RectangleShape Reflect[BAR_COUNT];
  float BarWidth = WIDTH / (float)BAR_COUNT;
  sf::Color MakeColor(float loudness);
  float amplitudes[BAR_COUNT] = {0};
};

#endif
