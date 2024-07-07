/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** draw
*/

#include "SFMLGraphics.hpp"

using namespace gui;

void SFMLGraphics::initCorner()
{
    CornerRect[0] = sf::IntRect(256, 192, tileSize, tileSize);
    CornerRect[1] = sf::IntRect(320, 192, tileSize, tileSize);
    CornerRect[2] = sf::IntRect(384, 192, tileSize, tileSize);
    CornerRect[3] = sf::IntRect(256, 256, tileSize, tileSize);
    CornerRect[4] = sf::IntRect(384, 256, tileSize, tileSize);
    CornerRect[5] = sf::IntRect(256, 320, tileSize, tileSize);
    CornerRect[6] = sf::IntRect(320, 320, tileSize, tileSize);
    CornerRect[7] = sf::IntRect(384, 320, tileSize, tileSize);
}

void SFMLGraphics::initResources()
{
    resourceRects[gui::Item::FOOD] = sf::IntRect(256, 0, tileSize, tileSize);
    resourceRects[gui::Item::LINEMATE] = sf::IntRect(320, 0, tileSize, tileSize);
    resourceRects[gui::Item::DERAUMERE] = sf::IntRect(384, 0, tileSize, tileSize);
    resourceRects[gui::Item::SIBUR] = sf::IntRect(448, 0, tileSize, tileSize);
    resourceRects[gui::Item::MENDIANE] = sf::IntRect(512, 0, tileSize, tileSize);
    resourceRects[gui::Item::PHIRAS] = sf::IntRect(576, 0, tileSize, tileSize);
    resourceRects[gui::Item::THYSTAME] = sf::IntRect(640, 0, tileSize, tileSize);
}

void SFMLGraphics::initPlayer()
{
    playerRects[gui::Orientation::UP][1] = sf::IntRect(0, 0, tileSize, tileSize);
    playerRects[gui::Orientation::UP][2] = sf::IntRect(0, 192, tileSize, tileSize);
    playerRects[gui::Orientation::UP][3] = sf::IntRect(0, 384, tileSize, tileSize);
    playerRects[gui::Orientation::UP][4] = sf::IntRect(0, 576, tileSize, tileSize);
    playerRects[gui::Orientation::UP][5] = sf::IntRect(0, 768, tileSize, tileSize);
    playerRects[gui::Orientation::UP][6] = sf::IntRect(0, 960, tileSize, tileSize);
    playerRects[gui::Orientation::UP][7] = sf::IntRect(0, 1152, tileSize, tileSize);
    playerRects[gui::Orientation::UP][8] = sf::IntRect(0, 1344, tileSize, tileSize);

    playerRects[gui::Orientation::RIGHT][1] = sf::IntRect(64, 0, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][2] = sf::IntRect(64, 192, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][3] = sf::IntRect(64, 384, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][4] = sf::IntRect(64, 576, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][5] = sf::IntRect(64, 768, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][6] = sf::IntRect(64, 960, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][7] = sf::IntRect(64, 1152, tileSize, tileSize);
    playerRects[gui::Orientation::RIGHT][8] = sf::IntRect(64, 1344, tileSize, tileSize);

    playerRects[gui::Orientation::DOWN][1] = sf::IntRect(128, 0, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][2] = sf::IntRect(128, 192, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][3] = sf::IntRect(128, 384, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][4] = sf::IntRect(128, 576, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][5] = sf::IntRect(128, 768, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][6] = sf::IntRect(128, 960, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][7] = sf::IntRect(128, 1152, tileSize, tileSize);
    playerRects[gui::Orientation::DOWN][8] = sf::IntRect(128, 1344, tileSize, tileSize);

    playerRects[gui::Orientation::LEFT][1] = sf::IntRect(192, 0, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][2] = sf::IntRect(192, 192, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][3] = sf::IntRect(192, 384, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][4] = sf::IntRect(192, 576, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][5] = sf::IntRect(192, 768, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][6] = sf::IntRect(192, 960, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][7] = sf::IntRect(192, 1152, tileSize, tileSize);
    playerRects[gui::Orientation::LEFT][8] = sf::IntRect(192, 1344, tileSize, tileSize);

    elevatingPlayerRects[gui::Orientation::UP][1] = sf::IntRect(0, 64, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][2] = sf::IntRect(0, 256, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][3] = sf::IntRect(0, 448, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][4] = sf::IntRect(0, 640, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][5] = sf::IntRect(0, 832, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][6] = sf::IntRect(0, 1024, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][7] = sf::IntRect(0, 1216, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::UP][8] = sf::IntRect(0, 1408, tileSize, tileSize);

    elevatingPlayerRects[gui::Orientation::RIGHT][1] = sf::IntRect(64, 64, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][2] = sf::IntRect(64, 256, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][3] = sf::IntRect(64, 448, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][4] = sf::IntRect(64, 640, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][5] = sf::IntRect(64, 832, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][6] = sf::IntRect(64, 1024, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][7] = sf::IntRect(64, 1216, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::RIGHT][8] = sf::IntRect(64, 1408, tileSize, tileSize);

    elevatingPlayerRects[gui::Orientation::DOWN][1] = sf::IntRect(128, 64, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][2] = sf::IntRect(128, 256, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][3] = sf::IntRect(128, 448, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][4] = sf::IntRect(128, 640, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][5] = sf::IntRect(128, 832, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][6] = sf::IntRect(128, 1024, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][7] = sf::IntRect(128, 1216, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::DOWN][8] = sf::IntRect(128, 1408, tileSize, tileSize);

    elevatingPlayerRects[gui::Orientation::LEFT][1] = sf::IntRect(192, 64, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][2] = sf::IntRect(192, 256, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][3] = sf::IntRect(192, 448, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][4] = sf::IntRect(192, 640, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][5] = sf::IntRect(192, 832, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][6] = sf::IntRect(192, 1024, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][7] = sf::IntRect(192, 1216, tileSize, tileSize);
    elevatingPlayerRects[gui::Orientation::LEFT][8] = sf::IntRect(192, 1408, tileSize, tileSize);
}

void SFMLGraphics::initEgg()
{
    EggRects = sf::IntRect(256, 64, tileSize, tileSize);
}

void SFMLGraphics::initSound()
{
    // SoundBuffer = loadSound("gui/assets/Level-Up.ogg");
    // Sound.setBuffer(SoundBuffer);
}
