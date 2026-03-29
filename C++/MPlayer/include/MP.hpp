#pragma once

#include "Visual.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
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
    bool Init_Music(std::string& musicpath);
    bool If_File_MP4(const std::string& filepath);
    std::string Convert_MP4_To_Wave(std::string& filepath);
    void LoadAndPlay(std::string& filepath);
    void Increase_Volume();
    void Decrease_Volume();
    void Increase_Speed();
    void Decrease_Speed();
    void Mute_Volume();
    float Get_Volume();

private:
    void drawText(sf::RenderWindow& window);
    void setupTextStyle(sf::Text& txt, const std::string& str, sf::Color color, float x, float y);

    sf::Font font;
    sf::Text text;
    sf::Text muteText;
    sf::Text playText;
    Visual visual;
    const sf::Vector2i windowPosition = {350, 100};
    const sf::Color backgroundColor = {20, 20, 30, 255};
    std::string currentTrack;
    sf::RenderWindow* window;
    sf::Music* music;
    bool isRunning = false;
    bool muteMusic = false;
    float currentSpeed = 1.0f;
    std::string mp4File;
    std::string wavFile;
    bool isTempFile = false;
};
