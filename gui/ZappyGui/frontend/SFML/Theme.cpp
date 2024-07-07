/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Theme
*/

#include "Theme.hpp"
#include "SFMLGraphics.hpp"

gui::Theme::Theme(): _atlas(nullptr), _ngAtlas(nullptr), _song(nullptr), _soundBuffer(new sf::SoundBuffer) {}

gui::Theme::~Theme()
{
    if (this->_atlas)
        delete this->_atlas;
    if (this->_ngAtlas)
        delete this->_ngAtlas;
    if (this->_song)
        delete this->_song;
    delete this->_soundBuffer;
}

const std::string &gui::Theme::getName(void) const
{
    return this->_name;
}

const sf::Keyboard::Key &gui::Theme::getKey(void) const
{
    return this->_key;
}

sf::Texture *gui::Theme::getAtlas(void)
{
    return this->_atlas;
}

sf::Texture *gui::Theme::getNGAtlas(void)
{
    return this->_ngAtlas;
}

sf::Sound *gui::Theme::getSong(void)
{
    return this->_song;
}

sf::Color gui::Theme::getBgColor(void)
{
    return this->_bgColor;
}

gui::Theme &gui::Theme::setKey(const sf::Keyboard::Key &key)
{
    this->_key = key;
    return *this;
}

gui::Theme &gui::Theme::setName(const std::string &name)
{
    this->_name = name;
    return *this;
}

gui::Theme &gui::Theme::setAtlas(const std::string &path)
{
    sf::Texture *texture = new sf::Texture;
    if (!texture->loadFromFile(path)) {
        throw ErrorTextureLoading("Error to load texture from " + path);
    }
    if (this->_atlas)
        delete this->_atlas;
    this->_atlas = texture;
    return *this;
}

gui::Theme &gui::Theme::setNGAtlas(const std::string &path)
{
    sf::Texture *texture = new sf::Texture;
    if (!texture->loadFromFile(path)) {
        throw ErrorTextureLoading("Error to load texture from " + path);
    }
    if (this->_ngAtlas)
        delete this->_ngAtlas;
    this->_ngAtlas = texture;
    return *this;
}

gui::Theme &gui::Theme::setSong(const std::string &path)
{
    sf::Sound *sound = new sf::Sound;
    if (!_soundBuffer->loadFromFile(path)) {
        throw ErrorTextureLoading("Error to load sound from " + path);
    }
    if (this->_song)
        delete this->_song;
    sound->setBuffer(*_soundBuffer);
    this->_song = sound;
    return *this;
}

gui::Theme &gui::Theme::setBgColor(const sf::Color &color)
{
    this->_bgColor = color;
    return *this;
}
