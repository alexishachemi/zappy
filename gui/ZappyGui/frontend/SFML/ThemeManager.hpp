/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ThemeManager
*/

#pragma once

#include "Theme.hpp"
#include "error.hpp"

namespace gui
{
    class ThemeManager
    {
        std::vector<std::unique_ptr<Theme>> _themes;
        Theme *_currentTheme;
        Theme *_defaultTheme;

        public:
            ThemeManager(
                const std::string &name,
                const sf::Keyboard::Key &key,
                const std::string &atlas,
                const std::string &ngAtlas,
                const std::string &song,
                const sf::Color &color
            );
            Theme *currentTheme();
            Theme *addTheme(
                const std::string &name,
                const sf::Keyboard::Key &key,
                const std::string &atlas,
                const std::string &ngAtlas,
                const std::string &song,
                const sf::Color &color
            );
            bool changeTheme(const std::string &name);
            bool changeTheme(const sf::Keyboard::Key &key);

        NEW_ERROR(ThemeManagerError);

        private:
            Theme *getTheme(const sf::Keyboard::Key key);
            Theme *getTheme(const std::string &name);
    };
}
