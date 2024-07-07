/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** frontend
*/

#include "SFMLGraphics.hpp"

using namespace gui;

void SFMLGraphics::initMouse()
{
    if (_event.type == sf::Event::MouseMoved) {
        mouse.x = _event.mouseMove.x;
        mouse.y = _event.mouseMove.y;
    } else if (_event.type == sf::Event::MouseButtonPressed) {
        mouse.x = _event.mouseButton.x;
        mouse.y = _event.mouseButton.y;
    }
}

void SFMLGraphics::handleMouseEvents(const Backend &b)
{
    sf::Vector2f worldMouse = _win.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y), view);

    float tileSize = 62.0f;
    mouseOnTile = false;

    for (int i = 0; i < b.getMapSize().x; ++i) {
        for (int j = 0; j < b.getMapSize().y; ++j) {
            if ((worldMouse.x >= (i * tileSize) && worldMouse.x < ((i + 1) * tileSize)) && 
                (worldMouse.y >= (j * tileSize) && worldMouse.y < ((j + 1) * tileSize))) {
                mouseOnTile = true;
                mousePosOnTile.x = i;
                mousePosOnTile.y = j;
                if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) {
                    clickedOnTile = true;
                    clickedTilePos.x = i;
                    clickedTilePos.y = j;
                }
            }
        }
    }
}

void SFMLGraphics::handleKeyboardEvents(const Backend &b)
{
    sf::Sound *sound = themeManager.currentTheme()->getSong();
    if (_event.key.code == sf::Keyboard::Escape) {
        clickedOnTile = false;
    }
    if (_event.key.code == sf::Keyboard::BackSpace) {
        sound->stop();
    }
    if (_event.key.code == sf::Keyboard::Up && _event.type == sf::Event::KeyPressed) {
        if (volume < 91) {
            volume += 10;
        }
        sound->setVolume(volume);
    }
    if (_event.key.code == sf::Keyboard::Down && _event.type == sf::Event::KeyPressed) {
        if (volume > 9) {
            volume -= 10;
        }
        sound->setVolume(volume);
    }
    if (_event.key.code == sf::Keyboard::Enter) {
        themeManager.changeTheme("default");
        sound = themeManager.currentTheme()->getSong();
        sound->setVolume(volume);
        sound->setLoop(true);
        sound->play();
    }
    if (_event.key.code == sf::Keyboard::G && _event.type == sf::Event::KeyPressed) {
        grid = !grid;
        updateAtlas();
    }
    if (_event.type == sf::Event::KeyPressed && themeManager.changeTheme(_event.key.code)) {
        sound = themeManager.currentTheme()->getSong();
        sound->setVolume(volume);
        sound->setLoop(true);
        sound->play();
        updateAtlas();
    }
}
