/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Theme
*/

#pragma once

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "error.hpp"

namespace gui
{
    class Theme
    {
        std::string _name;
        sf::Keyboard::Key _key;
        sf::Texture *_atlas;
        sf::Texture *_ngAtlas;
        sf::Sound *_song;
        sf::SoundBuffer *_soundBuffer;
        sf::Color _bgColor;

        public:
            Theme();
            ~Theme();
            const std::string &getName(void) const;
            const sf::Keyboard::Key &getKey(void) const;
            sf::Texture *getAtlas(void);
            sf::Texture *getNGAtlas(void);
            sf::Sound *getSong(void);
            sf::Color getBgColor(void);
            Theme &setKey(const sf::Keyboard::Key &key);
            Theme &setName(const std::string &name);
            Theme &setAtlas(const std::string &path);
            Theme &setNGAtlas(const std::string &path);
            Theme &setSong(const std::string &path);
            Theme &setBgColor(const sf::Color &color);
    };
}
