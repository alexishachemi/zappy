/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RL2DRenderer
*/

#include "RL2DRenderer.hpp"
#include "raymath.h"

gui::RL2DRenderer::RL2DRenderer()
{
    randomSeed = std::time(nullptr);
    if (!atlas.load(atlasPath, atlasCellSize))
        throw RL2DRendererError("Atlas not found");
    if (!music.load(musicPath))
        throw RL2DRendererError("Music not found");
}

std::string gui::RL2DRenderer::getName() const
{
    return "2d";
}

void gui::RL2DRenderer::update(const Backend &be)
{
    music.update();
    updateCamera(be);
    animationClock += GetFrameTime();
    if (animationClock >= animationFrameTime) {
        animationCounter++;
        animationClock = 0;
    }
}

void gui::RL2DRenderer::render(const Backend &be)
{
    ClearBackground(backgroundColor);
    BeginMode2D(camera);
    for (auto &tile : be) {
        drawTile(tile, be.getMapSize());
    }
    drawGroundCliff(be.getMapSize());
    EndMode2D();
}

void gui::RL2DRenderer::start()
{
    if (!music.isPlaying()) {
       music.play();
       music.setVolume(0.05);
    } else
        music.resume();
}

void gui::RL2DRenderer::stop()
{
    music.pause();
}

void gui::RL2DRenderer::drawAtlas(Vec2 gridPosition, Vec2 atlasPosition, Vector2 offset)
{
    atlas.draw(Vector2Add(gridToScreenPos(gridPosition), offset), atlasPosition);
}

void gui::RL2DRenderer::drawTile(const Tile &tile, Vec2 mapSize)
{
    drawAtlas(tile.pos, getGroundTilePos(tile.pos, mapSize));
    for (Item item = Item::FOOD; item <= Item::THYSTAME; item = static_cast<Item>(static_cast<int>(item) + 1)) {
        if (tile.inventory[item] > 0) {
            drawItem(item, tile.pos);
        }
    }
    if (!tile.eggs.empty()) {
        drawEgg(tile.pos);
    }
    for (const Player *player : tile.players) {
        drawPlayer(*player);
    }
}

void gui::RL2DRenderer::drawPlayer(const Player &player)
{
    Vec2 atlasPosition = {0, (static_cast<int>(player.getLevel()) - 1) * 3};

    if (player.isElevating()) {
        atlasPosition.y += 1;
    } else if (player.isLaying()) {
        atlasPosition.y += 2;
    }
    atlasPosition.x = static_cast<int>(player.getOrientation()) - 1;
    drawAtlas(player.getPos(), atlasPosition);
}

void gui::RL2DRenderer::drawItem(Item item, Vec2 gridPosition)
{
    Vec2 atlasPosition = {4 + static_cast<int>(item), 0};
    Vec2 offsetI = {
        getRandomDeterministic(-atlasCellSize / 4, atlasCellSize / 4, randomSeed * static_cast<int>(item)),
        getRandomDeterministic(-atlasCellSize / 4, atlasCellSize / 4, randomSeed * static_cast<int>(item))
    };
    Vector2 offset = {static_cast<float>(offsetI.x), static_cast<float>(offsetI.y)};

    drawAtlas(gridPosition, atlasPosition, offset);
}

void gui::RL2DRenderer::drawEgg(Vec2 gridPosition)
{
    drawAtlas(gridPosition, {4 + animationCounter % 6, 1});
}

Vector2 gui::RL2DRenderer::gridToScreenPos(Vec2 gridPosition) const
{
    Vec2 pxPosition = gridPosition * Vec2(atlasCellSize, atlasCellSize);

    return {static_cast<float>(pxPosition.x), static_cast<float>(pxPosition.y)};
}

void gui::RL2DRenderer::updateCamera(const Backend &be)
{
    float wheel = GetMouseWheelMove();
    Vec2 mapSize = be.getMapSize();

    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.offset = GetMousePosition();
        camera.target = mouseWorldPos;
        float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
        if (wheel < 0) {
            scaleFactor = 1.0f / scaleFactor;
        }
        camera.zoom = Clamp(camera.zoom * scaleFactor, minZoom, maxZoom);
    }
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        camera.target = Vector2Add(camera.target, Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom));
    }
    if (IsKeyPressed(KEY_SPACE)) {
        centerCamera(be);
    } else if (be.getMapSize() != lastMapSize) {
        lastMapSize = be.getMapSize();
        centerCamera(be);
    }
    camera.target.x = Clamp(camera.target.x, 0, (mapSize.x * atlasCellSize));
    camera.target.y = Clamp(camera.target.y, 0, (mapSize.y * atlasCellSize));
}

void gui::RL2DRenderer::centerCamera(const Backend &be)
{
    Vec2 mapSize = be.getMapSize();
    int maxTileSize = std::max(mapSize.x, mapSize.y);
    Vector2 currentScreenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};

    camera.zoom = std::min(currentScreenSize.x / (maxTileSize * atlasCellSize), currentScreenSize.y / (maxTileSize * atlasCellSize));
    camera.target = {mapSize.x * atlasCellSize / 2.0f, mapSize.y * atlasCellSize / 2.0f};
    camera.offset = {currentScreenSize.x / 2.0f, currentScreenSize.y / 2.0f};
    camera.zoom -= 0.1f;
    minZoom = camera.zoom / 1.5f;
    maxZoom = camera.zoom * 4.5f;
}

void gui::RL2DRenderer::drawGroundCliff(Vec2 mapSize)
{
    if (mapSize == Vec2(1, 1)) {
        drawAtlas({0, 1}, {7, 6});
        return;
    }
    drawAtlas({0, mapSize.y}, {4, 6});
    for (int i = 1; i < mapSize.x - 1; i++) {
        drawAtlas({i, mapSize.y}, {5, 6});
    }
    drawAtlas({mapSize.x - 1, mapSize.y}, {6, 6});
}

gui::Vec2 gui::RL2DRenderer::getGroundTilePos(Vec2 tilePosition, Vec2 mapSize)
{
    Vec2 pos;

    if (mapSize.x == 1 && mapSize.y == 1)
        return getSingleTilePos();
    if (mapSize.x == 1)
        return getSlimVTilePos(tilePosition, mapSize);
    if (mapSize.y == 1)
        return getSlimHTilePos(tilePosition, mapSize);
    if (tilePosition.y == 0)
        pos.y = 2;
    else if (tilePosition.y == mapSize.y - 1)
        pos.y = 4;
    else
        pos.y = 3;
    if (tilePosition.x == 0)
        pos.x = 4;
    else if (tilePosition.x == mapSize.x - 1)
        pos.x = 6;
    else
        pos.x = 5;
    return pos;
}

gui::Vec2 gui::RL2DRenderer::getSingleTilePos()
{
    return {7, 5};
}

gui::Vec2 gui::RL2DRenderer::getSlimHTilePos(Vec2 tilePosition, Vec2 mapSize)
{
    Vec2 pos = {4, 5};

    if (tilePosition.x == 0)
        pos.x = 4;
    else if (tilePosition.x == mapSize.x - 1)
        pos.x = 6;
    else
        pos.x = 5;
    return pos;
}

gui::Vec2 gui::RL2DRenderer::getSlimVTilePos(Vec2 tilePosition, Vec2 mapSize)
{
    Vec2 pos = {7, 2};

    if (tilePosition.y == 0)
        pos.y = 2;
    else if (tilePosition.y == mapSize.y - 1)
        pos.y = 4;
    else
        pos.y = 3;
    return pos;
}

int gui::RL2DRenderer::getRandomDeterministic(int min, int max, int seed)
{
    std::hash<int> hasher;

    return (hasher(seed) % (max - min + 1)) + min;
}
