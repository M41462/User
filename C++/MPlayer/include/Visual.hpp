#ifndef VISUAL_HPP
#define VISUAL_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <cmath>

constexpr int WIDTH = 700;
constexpr int HEIGHT = 600;
constexpr int BAR_COUNT = 128;

class Visual {
public:
    void Set_Visual();
    void Update_Visual(sf::Music& music);
    void Draw_Visual(sf::RenderWindow& window);

private:
    sf::Color MakeColor(float loudness);
    float CalculateAmplitude(float time, float frequency, int index);
    
    sf::RectangleShape Bars[BAR_COUNT];
    sf::RectangleShape Reflect[BAR_COUNT];
    const float BarWidth = WIDTH / static_cast<float>(BAR_COUNT);
    float amplitudes[BAR_COUNT] = {0};
};

#endif
