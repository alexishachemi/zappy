/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** frontend
*/

#include "SFMLGraphics.hpp"

using namespace gui;

sf::Sprite SFMLGraphics::loadSprite(sf::Texture text, sf::Vector2f pos)
{
    sf::Sprite sprite;

    this->sprite_loaded = true;
    return sprite;
}

sf::Font SFMLGraphics::loadFont(std::string path)
{
    sf::Font font;
    if (!font.loadFromFile(path)) {
        throw ErrorFontLoading("Error to load font");
    }
    this->font_loaded = true;
    return font;
}

sf::SoundBuffer SFMLGraphics::loadSound(const std::string &path)
{
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(path))
    {
        throw ErrorTextureLoading("Error to load sound from " + path);
    }
    return soundBuffer;
}

sf::Sound SFMLGraphics::CreateSound(std::string path)
{
    SoundBuffer = loadSound(path);
    themeManager.currentTheme()->getSong()->setBuffer(SoundBuffer);
    return *themeManager.currentTheme()->getSong();
}
