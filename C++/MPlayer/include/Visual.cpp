#include "Visual.hpp"
#include <SFML/System/Mutex.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>

void Visual::Set_Visual() {
  for (int i = 0; i < BAR_COUNT; i++) {
    Bars[i].setSize(sf::Vector2f(BarWidth, 10));
    Bars[i].setPosition(i * BarWidth, (float)HEIGHT / 2 + 250);
    Bars[i].setFillColor(sf::Color::Cyan);

    Reflect[i].setSize(sf::Vector2f(BarWidth - 2, 5));
    Reflect[i].setPosition(i * BarWidth, (float)HEIGHT / 2 + 250);
    Reflect[i].setFillColor(sf::Color(100, 255, 255, 100));
  }
}

sf::Color Visual::MakeColor(float loudness) {
  loudness = std::max(0.0f, std::min(loudness, 1.0f));
  return sf::Color(0, 150 + (int)(loudness * 105), 200 + (int)(loudness * 55));
}

void Visual::Update_Visual(sf::Music &music) {
  sf::Time offset = music.getPlayingOffset();

  for (int i = 0; i < BAR_COUNT; i++) {
    float time = offset.asSeconds();
    float frequency = 0.1f + (i * 0.05f);

    float amplitude = 0.5f + 0.5f * sin(time * frequency * 5.0f);

    amplitudes[i] = 0.9f * amplitudes[i] + 0.1f * amplitude;

    float height = 100 + amplitudes[i] * 300;
    Bars[i].setSize(sf::Vector2f(BarWidth - 2, -height));
    Bars[i].setFillColor(MakeColor(amplitudes[i]));
  }
}

void Visual::Draw_Visual(sf::RenderWindow &window) {
  for (int i = 0; i < BAR_COUNT; i++) {
    window.draw(Bars[i]);
  }
}
