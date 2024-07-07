/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ThemeManager
*/

#include "ThemeManager.hpp"

using namespace gui;

gui::ThemeManager::ThemeManager(
    const std::string &name,
    const sf::Keyboard::Key &key,
    const std::string &atlas,
    const std::string &ngAtlas,
    const std::string &song,
    const sf::Color &color
)
{
    _defaultTheme = addTheme(name, key, atlas, ngAtlas, song, color);
    _currentTheme = _defaultTheme;
}

Theme *gui::ThemeManager::currentTheme()
{
    return _currentTheme;
}

Theme *gui::ThemeManager::addTheme(
    const std::string &name,
    const sf::Keyboard::Key &key,
    const std::string &atlas,
    const std::string &ngAtlas,
    const std::string &song,
    const sf::Color &color
)
{
    Theme *theme = new Theme();

    theme->setName(name);
    theme->setKey(key);
    theme->setAtlas(atlas);
    theme->setNGAtlas(ngAtlas);
    theme->setSong(song);
    theme->setBgColor(color);
    _themes.push_back(std::make_unique<Theme>(*theme));
    return theme;
}

bool gui::ThemeManager::changeTheme(const std::string &name)
{
    try {
        Theme *theme = getTheme(name);
        std::string themeName = theme->getName();
        std::string currentThemeName = currentTheme()->getName();
        if (themeName == currentThemeName && themeName != _defaultTheme->getName()) {
            _currentTheme = _defaultTheme;
        } else {
            _currentTheme = theme;
        }
        for (auto &theme : this->_themes) {
            theme->getSong()->stop();
        }
        return true;
    } catch (ThemeManagerError &e) {
        return false;
    }
}

bool gui::ThemeManager::changeTheme(const sf::Keyboard::Key &key)
{
    try {
        Theme *theme = getTheme(key);
        sf::Keyboard::Key themeKey = theme->getKey();
        sf::Keyboard::Key defaultKey = _defaultTheme->getKey();
        if (themeKey == currentTheme()->getKey() && themeKey != defaultKey) {
            _currentTheme = _defaultTheme;
        } else {
            _currentTheme = theme;
        }
        for (auto &theme : this->_themes) {
            theme->getSong()->stop();
        }
        return true;
    } catch (ThemeManagerError &e) {
        return false;
    }
}

Theme *gui::ThemeManager::getTheme(const sf::Keyboard::Key key)
{
    for (auto &theme : _themes) {
        if (theme->getKey() == key) {
            return theme.get();
        }
    }
    throw ThemeManagerError("No theme with key " + std::to_string(static_cast<int>(key)) + " assigned");
}

Theme *gui::ThemeManager::getTheme(const std::string &name)
{
    for (auto &theme : _themes) {
        if (theme->getName() == name) {
            return theme.get();
        }
    }
    throw ThemeManagerError("No theme with name " + name);
}
