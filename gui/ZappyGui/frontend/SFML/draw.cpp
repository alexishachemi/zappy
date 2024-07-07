/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** draw
*/

#include "SFMLGraphics.hpp"

using namespace gui;

void SFMLGraphics::draw(const Backend &b)
{
    // if (!texture_loaded) {
    //     throw ErrorTextureLoading("Error loading texture from \n");
    // }
    drawMap(b);
    drawCorner(b);
    if (clickedOnTile) {
        drawTileInfo(b);
    }
    for (auto &tile : b) {
        drawResources(b, tile);
        drawPlayer(b, tile);
        drawEgg(b, tile);
    }
    _win.display();
}

void SFMLGraphics::drawMap(const Backend &b)
{
    sf::Vector2u windowSize = _win.getSize();

    Vec2 mapSize = b.getMapSize();

    int tileSize = 62;

    sf::IntRect textureRect(256, 128, tileSize, tileSize);
    sf::IntRect textureSelectedRect(321, 128, tileSize, tileSize);

    sf::Sprite tileSprite;
    tileSprite.setTexture(*textureA);
    tileSprite.setTextureRect(textureRect);
    tileSprite.setScale(tileSize / static_cast<float>(textureRect.width),
                        tileSize / static_cast<float>(textureRect.height));
    sf::Sprite tileSelectedSprite;
    tileSelectedSprite.setTexture(*textureA);
    tileSelectedSprite.setTextureRect(textureSelectedRect);
    tileSelectedSprite.setScale(tileSize / static_cast<float>(textureSelectedRect.width),
                        tileSize / static_cast<float>(textureSelectedRect.height));

    for (int i = 0; i < mapSize.x; ++i) {
        for (int j = 0; j < mapSize.y; ++j) {
            tileSprite.setPosition(i * tileSize, j * tileSize);
            _win.draw(tileSprite);
            if (mouseOnTile) {
                tileSelectedSprite.setPosition(mousePosOnTile.x * tileSize, mousePosOnTile.y * tileSize);
                _win.draw(tileSelectedSprite);
            }
            if (clickedOnTile) {
                tileSelectedSprite.setPosition(clickedTilePos.x * tileSize, clickedTilePos.y * tileSize);
                _win.draw(tileSelectedSprite);
            }
        }
    }
}

void SFMLGraphics::drawSprite(sf::Sprite sprite, sf::Vector2f pos)
{
    sprite.setPosition(pos);
    _win.draw(sprite);
}

sf::Sprite SFMLGraphics::CreateSprite(sf::Texture &texture, gui::Vec2 recPos)
{
    sf::Sprite food;
    sf::IntRect food_rect(recPos.x, recPos.y, tileSize, tileSize);
    food.setTexture(texture);
    food.setTextureRect(food_rect);
    return food;
}

void SFMLGraphics::drawTileInfo(const Backend &b)
{
    int tileSize = 62;

    sf::Vector2f viewCenter = _win.getView().getCenter();
    sf::Vector2f viewSize = _win.getView().getSize();
    sf::Vector2f viewTopLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

    float scaleFactor = viewSize.y / 600.0f;

    sf::Vector2f rectSize((b.getMapSize().x / 2) * tileSize, (b.getMapSize().y) * tileSize);
    sf::Vector2f rectPosition(viewTopLeft.x + tileSize * b.getMapSize().x + (tileSize * 3), viewCenter.y - rectSize.y / 2);

    sf::RectangleShape rect(rectSize);
    rect.setFillColor(sf::Color(200, 200, 200, 100));
    rect.setPosition(rectPosition);

    if (b.getMapSize() == Vec2(0, 0)) {
        return;
    }

    std::string content = 
    "Tile position : " + std::to_string(b.getTile(clickedTilePos).pos.x) + " : " + std::to_string(b.getTile(clickedTilePos).pos.y) + "\n\n" +
    "Food : " + std::to_string(b.getTile(clickedTilePos).inventory.food) + "\n\n" +
    "Linemate : " + std::to_string(b.getTile(clickedTilePos).inventory.deraumere) + "\n\n" +
    "Deraumere : " + std::to_string(b.getTile(clickedTilePos).inventory.linemate) + "\n\n" +
    "Sibur : " + std::to_string(b.getTile(clickedTilePos).inventory.thystame) + "\n\n" +
    "Mendiane : " + std::to_string(b.getTile(clickedTilePos).inventory.sibur) + "\n\n" +
    "Phiras : " + std::to_string(b.getTile(clickedTilePos).inventory.mendiane) + "\n\n" +
    "Thystame : " + std::to_string(b.getTile(clickedTilePos).inventory.phiras) + "\n\n" +
    "Egg : " + std::to_string(b.getTile(clickedTilePos).eggs.size());
    sf::Text text(content, font);
    text.setCharacterSize(static_cast<unsigned int>(24 * scaleFactor));
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(rect.getSize().x / 2 - 50 * scaleFactor, textRect.top + textRect.height / 2.0f);
    text.setPosition(rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f);

    sf::Sprite food = CreateSprite(*textureA, {256, 384});
    sf::Sprite linemate = CreateSprite(*textureA, {320, 384});
    sf::Sprite deraumere = CreateSprite(*textureA, {384, 384});
    sf::Sprite sibur = CreateSprite(*textureA, {448, 384});
    sf::Sprite mendiane = CreateSprite(*textureA, {512, 384});
    sf::Sprite phiras = CreateSprite(*textureA, {576, 384});
    sf::Sprite thystame = CreateSprite(*textureA, {640, 384});
    sf::Sprite egg = CreateSprite(*textureA, {704, 384});

    food.setScale(scaleFactor, scaleFactor);
    linemate.setScale(scaleFactor, scaleFactor);
    deraumere.setScale(scaleFactor, scaleFactor);
    sibur.setScale(scaleFactor, scaleFactor);
    mendiane.setScale(scaleFactor, scaleFactor);
    phiras.setScale(scaleFactor, scaleFactor);
    thystame.setScale(scaleFactor, scaleFactor);
    egg.setScale(scaleFactor, scaleFactor);

    _win.draw(rect);
    drawSprite(food, {rect.getPosition().x, rect.getPosition().y + 40 * scaleFactor});
    drawSprite(linemate, {rect.getPosition().x, rect.getPosition().y + 100 * scaleFactor});
    drawSprite(deraumere, {rect.getPosition().x, rect.getPosition().y + 160 * scaleFactor});
    drawSprite(sibur, {rect.getPosition().x, rect.getPosition().y + 220 * scaleFactor});
    drawSprite(mendiane, {rect.getPosition().x, rect.getPosition().y + 277 * scaleFactor});
    drawSprite(phiras, {rect.getPosition().x, rect.getPosition().y + 335 * scaleFactor});
    drawSprite(thystame, {rect.getPosition().x, rect.getPosition().y + 390 * scaleFactor});
    drawSprite(egg, {rect.getPosition().x, rect.getPosition().y + 450 * scaleFactor});
    _win.draw(text);
}

void SFMLGraphics::drawResources(const Backend &b, const Tile &tile)
{
    sf::Vector2f spritePos;
    initResources();

    int tileSize = 62;

    spritePos.x = tile.pos.x * tileSize;
    spritePos.y = tile.pos.y * tileSize;

    sf::Sprite sprite;
    sprite.setTexture(*textureA);
    for (const auto &resource : resourceRects) {
        gui::Item resourceType = resource.first;
        int resourceCount = tile.inventory.get(resourceType);
        if (resourceCount > 0) {
            sprite.setTextureRect(resource.second);
            drawSprite(sprite, spritePos);
        }
    }
}

void SFMLGraphics::playLevelUpSound()
{
    // Sound.play();
}

void SFMLGraphics::drawPlayer(const Backend &b, const Tile &tile)
{
    int tileSize = 62;
    for (auto player : tile.players) {
        Vec2 playerPos = tile.pos;
        Orientation playerOrientation = player->getOrientation();
        int playerLevel = player->getLevel();
        sf::IntRect spriteRect;

        if (player->isElevating()) {
            spriteRect = elevatingPlayerRects[playerOrientation][playerLevel];
            playLevelUpSound();
        } else {
            spriteRect = playerRects[playerOrientation][playerLevel];
        }
        sf::Vector2f position(playerPos.x * tileSize, playerPos.y * tileSize);
        sf::Sprite playerSprite;
        playerSprite.setTexture(*textureA);
        playerSprite.setTextureRect(spriteRect);
        drawSprite(playerSprite, position);
    }
}

void SFMLGraphics::drawEgg(const Backend &b, const Tile &tile)
{
    initEgg();

    int tileSize = 62;
    for (int i = 0; i < tile.eggs.size(); i++) {
        Vec2 EggPos = tile.pos;

        sf::Vector2f position(EggPos.x * tileSize, EggPos.y * tileSize);
        sf::Sprite EggSprite;
        EggSprite.setTexture(*textureA);
        EggSprite.setTextureRect(EggRects);
        drawSprite(EggSprite, position);
    }
}

void SFMLGraphics::drawCorner(const Backend &b)
{
    sf::Sprite cornerSprite;
    cornerSprite.setTexture(*textureA);

    int tileSize = 62;
    Vec2 mapSize = b.getMapSize();

    int extendedWidth = mapSize.x + 2;
    int extendedHeight = mapSize.y + 2;

    for (int i = -1; i <= mapSize.x; ++i) {
        for (int j = -1; j <= mapSize.y; ++j) {
            if (i == -1 && j == -1) {
                cornerSprite.setTextureRect(CornerRect[0]);
            } else if (i == mapSize.x && j == -1) {
                cornerSprite.setTextureRect(CornerRect[2]);
            } else if (i == -1 && j == mapSize.y) {
                cornerSprite.setTextureRect(CornerRect[5]);
            } else if (i == mapSize.x && j == mapSize.y) {
                cornerSprite.setTextureRect(CornerRect[7]);
            } else if (i == -1) {
                cornerSprite.setTextureRect(CornerRect[3]);
            } else if (i == mapSize.x) {
                cornerSprite.setTextureRect(CornerRect[4]);
            } else if (j == -1) {
                cornerSprite.setTextureRect(CornerRect[1]);
            } else if (j == mapSize.y) {
                cornerSprite.setTextureRect(CornerRect[6]);
            } else {
                continue;
            }
            cornerSprite.setScale(tileSize / static_cast<float>(cornerSprite.getTextureRect().width),
                                  tileSize / static_cast<float>(cornerSprite.getTextureRect().height));
            cornerSprite.setPosition((i + 1 - 1) * tileSize, (j + 1 - 1) * tileSize);
            _win.draw(cornerSprite);
        }
    }
}
