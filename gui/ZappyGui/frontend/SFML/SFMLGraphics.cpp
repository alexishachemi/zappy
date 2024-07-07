/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** frontend
*/

#include "SFMLGraphics.hpp"

using namespace gui;

SFMLGraphics::SFMLGraphics()
    : themeManager(
        "default",
        sf::Keyboard::Enter,
        "gui/assets/atlas.png",
        "gui/assets/NG-atlas.png",
        "gui/assets/main_theme.ogg",
        sf::Color(25, 118, 157))
{
    themeManager.addTheme("Doom",
        sf::Keyboard::D,
        "gui/assets/D-atlas.png",
        "gui/assets/DNG-atlas.png",
        "gui/assets/Doom.ogg",
        sf::Color(74, 107, 85));
    themeManager.addTheme("Minecraft",
        sf::Keyboard::M,
        "gui/assets/M-atlas.png",
        "gui/assets/MNG-atlas.png",
        "gui/assets/Minecraft.ogg",
        sf::Color(123, 155, 198));
    themeManager.addTheme("Paint",
        sf::Keyboard::P,
        "gui/assets/P-atlas.png",
        "gui/assets/PNG-atlas.png",
        "gui/assets/Paint.ogg",
        sf::Color(25, 118, 157));
    updateAtlas();
    initWindow();
    initCorner();
    initResources();
    initPlayer();
    initSound();
    initEgg();
}

SFMLGraphics::~SFMLGraphics()
{
    deinitWindow();
}

int SFMLGraphics::initWindow()
{
    if (_win.isOpen()) {
        return 0;
    }
    _win.create(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Default);
    font = loadFont("gui/assets/Attractive-Regular.ttf");
    bgColor = sf::Color(25, 118, 157);
    _win.clear(bgColor);
    _win.setFramerateLimit(60);
    _win.display();
    return 0;
}

void SFMLGraphics::deinitWindow()
{
    if (!_win.isOpen()) {
        return;
    }
    _win.close();
}

bool SFMLGraphics::update(const Backend &b)
{
    if (!_win.isOpen()) {
        return false;
    }
    windowZoom(b);
    eventHandler(b);
    _win.clear(themeManager.currentTheme()->getBgColor());
    draw(b);
    _win.display();
    return true;
}

void SFMLGraphics::updateAtlas()
{
    if (grid) {
        textureA = themeManager.currentTheme()->getAtlas();
    } else {
        textureA = themeManager.currentTheme()->getNGAtlas();
    }
}

void SFMLGraphics::eventHandler(const Backend &b)
{
    while (_win.pollEvent(this->_event)) {
        initMouse();
        if (_event.type == sf::Event::Closed) {
            _win.close();
        }
        if (_event.type == sf::Event::MouseMoved || _event.type == sf::Event::MouseButtonReleased || _event.type == sf::Event::MouseButtonPressed) {
            handleMouseEvents(b);
        }
        if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::KeyReleased) {
            handleKeyboardEvents(b);
        }
    }
}

void SFMLGraphics::windowZoom(const Backend &b)
{
    sf::Vector2u windowSize = _win.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    gui::Vec2 mapSize = b.getMapSize();
    float mapWidth = static_cast<float>(mapSize.x) + 2;
    float mapHeight = static_cast<float>(mapSize.y) + 2;

    float tileSize = 62.0f;

    float totalMapWidth = mapWidth * tileSize;
    float totalMapHeight = mapHeight * tileSize;

    view = _win.getDefaultView();

    float scaleX = windowWidth / totalMapWidth;
    float scaleY = windowHeight / totalMapHeight;
    float scale = std::min(scaleX, scaleY);

    float initialViewCenterX = totalMapWidth / 2 - tileSize;
    float initialViewCenterY = totalMapHeight / 2 - tileSize;

    if (clickedOnTile) {
        view.setSize(windowWidth / scale, windowHeight / scale);
        scaleX = windowWidth / (totalMapWidth + (2 * tileSize));
        scaleY = windowHeight / totalMapHeight;
        scale = std::min(scaleX, scaleY);
        float newViewCenterX = (windowWidth / 2 / scale) - (tileSize * 2);
        view.setCenter(newViewCenterX, initialViewCenterY);
    } else {
        view.setSize(windowWidth / scale, windowHeight / scale);
        view.setCenter(initialViewCenterX, initialViewCenterY);
    }

    _win.setView(view);
}
