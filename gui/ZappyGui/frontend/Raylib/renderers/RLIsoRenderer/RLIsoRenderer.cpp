/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLIsoRenderer
*/

#include "RLIsoRenderer.hpp"
#include "raymath.h"

gui::RLIsoRenderer::RLIsoRenderer()
    : initialSeed(std::time(nullptr))
{
    if (!atlas.load(atlasPath, atlasCellSize))
        throw RLIsoRendererError("Atlas not found");
    if (!music.load(musicPath))
        throw RLIsoRendererError("Music not found");
}

std::string gui::RLIsoRenderer::getName() const
{
    return "isometric";
}

void gui::RLIsoRenderer::update(const Backend &be)
{
    if (showHud) {
        hud.update(be, *this);
        updateCursor(be.getMapSize());
    }
    music.update();
    if (!(showHud && hud.isPaused()))
        updateCamera(be);
    if (IsKeyPressed(KEY_O) || IsKeyPressed(KEY_W))
        showOcean = !showOcean;
    if (IsKeyPressed(KEY_I))
        showItems = !showItems;
    if (IsKeyPressed(KEY_H))
        showHud = !showHud;
    if (IsKeyPressed(KEY_P))
        showEggs = !showEggs;
    animationClock += GetFrameTime();
    if (animationClock >= animationFrameTime) {
        animationCounter++;
        animationClock = 0;
    }
}

void gui::RLIsoRenderer::render(const Backend &be)
{
    Vec2 mapSize = be.getMapSize();

    ClearBackground(backgroundColor);
    BeginMode2D(camera);
    if (showOcean) {
        drawAtlas({-1, -1}, {3, 8});
        drawAtlas({0, -1}, {3, 8});
        drawAtlas({-1, 0}, {3, 8});
    }
    for (int y = 0; y < mapSize.y; y++) {
        drawTileLine(be, {0, y}, mapSize);
    }
    for (int x = 1; x < mapSize.x; x++) {
        drawTileLine(be, {x, mapSize.y - 1}, mapSize);
    }
    if (showOcean) {
        drawAtlas({mapSize.x - 1, mapSize.y}, {3, 8});
        drawAtlas({mapSize.x, mapSize.y - 1}, {3, 8});
        drawAtlas(mapSize, {3, 8});
    }
    EndMode2D();
    if (showHud)
        hud.render(be, *this);
}

void gui::RLIsoRenderer::start()
{
    if (!music.isPlaying()) {
       music.play();
       music.setVolume(0.3f);
    } else
        music.resume();
}

void gui::RLIsoRenderer::stop()
{
    music.pause();
}

gui::RLAtlas &gui::RLIsoRenderer::getAtlas()
{
    return atlas;
}

gui::RLMusic &gui::RLIsoRenderer::getMusic()
{
    return music;
}

bool gui::RLIsoRenderer::tileSelected() const
{
    return cursorFixed;
}

bool gui::RLIsoRenderer::tileSelected(Vec2 &buf) const
{
    if (cursorFixed) {
        buf = cursorPos;
        return true;
    }
    return false;
}

void gui::RLIsoRenderer::drawTile(const Tile &tile, Vector2 position, Vector2 scale)
{
    atlas.draw(position, getRandomGroundTile(tile.pos), scale);
    atlas.draw(position, getRandomTileDecor(tile.pos), scale, groundOffset);
    for (Item item = Item::FOOD; item <= Item::THYSTAME && showItems; item = static_cast<Item>(static_cast<int>(item) + 1)) {
        if (tile.inventory[item] > 0) {
            drawItem(item, position, scale, true);
        }
    }
    if (!tile.eggs.empty() && showEggs) {
        atlas.draw(position, {10, 9}, scale, groundOffset);
        atlas.draw(position, {4 + (animationCounter + hashVec(tile.pos)) % 6, 9}, scale, groundOffset);
    }
    for (const Player *player : tile.players)
        drawPlayer(*player, position, scale);
}

void gui::RLIsoRenderer::drawItem(Item item, Vector2 position, Vector2 scale, bool tileRender)
{
    Vector2 offset = {0, 0};
    if (tileRender) {
        Vec2 offsetI = {
            getRandomDeterministic(-atlasCellSize / 16, atlasCellSize / 16, static_cast<int>(item)),
            getRandomDeterministic(-atlasCellSize / 16, atlasCellSize / 16, static_cast<int>(item))
        };
        offset = {static_cast<float>(offsetI.x) + groundOffset.x, static_cast<float>(offsetI.y) + groundOffset.y};
    }
    atlas.draw(position, getItemAtlasPos(item), scale, offset);
}

void gui::RLIsoRenderer::drawPlayer(const Player &player, Vector2 position, Vector2 scale)
{
    Vec2 atlasPosition = {0, static_cast<int>(player.getLevel()) - 1};
    Vec2 shadowAtlasPosition = {3, 9};

    atlasPosition.x = static_cast<int>(player.getOrientation()) - 1;
    if (player.isElevating())
        atlasPosition.x += 8;
    else if (player.isLaying())
        atlasPosition.x += 4;
    shadowAtlasPosition.y += player.isElevating();
    atlas.draw(position, shadowAtlasPosition, scale, groundOffset);
    atlas.draw(position, atlasPosition, scale, groundOffset);
}

gui::Vec2 gui::RLIsoRenderer::getItemAtlasPos(Item item) const
{
    return {4 + static_cast<int>(item), 8};
}

bool gui::RLIsoRenderer::getShowOcean() const
{
    return showOcean;
}

void gui::RLIsoRenderer::setShowOcean(bool showOcean)
{
    this->showOcean = showOcean;
}

bool gui::RLIsoRenderer::getShowItems() const
{
    return showItems;
}

void gui::RLIsoRenderer::setShowItems(bool showItems)
{
    this->showItems = showItems;
}

bool gui::RLIsoRenderer::getShowEggs() const
{
    return showEggs;
}

void gui::RLIsoRenderer::setShowEggs(bool showEggs)
{
    this->showEggs = showEggs;
}

Vector2 gui::RLIsoRenderer::gridToScreenPos(Vec2 gridPosition) const
{
    Vec2 pxPosition = {
        (gridPosition.x - gridPosition.y) * (atlasCellSize / 2),
        (gridPosition.x + gridPosition.y) * (atlasCellSize / 4)
    };

    return {static_cast<float>(pxPosition.x), static_cast<float>(pxPosition.y)};
}

gui::Vec2 gui::RLIsoRenderer::screenPosToGrid(Vector2 ScreenPosition) const
{
    Vec2 gridPosition = {
        static_cast<int>(ScreenPosition.x / (atlasCellSize / 2) + ScreenPosition.y / (atlasCellSize / 4)) / 2 - 1,
        static_cast<int>(ScreenPosition.y / (atlasCellSize / 4) - ScreenPosition.x / (atlasCellSize / 2)) / 2
    };

    return gridPosition;
}

void gui::RLIsoRenderer::drawAtlas(Vec2 gridPosition, Vec2 atlasPosition, Vector2 offset)
{
    atlas.draw(Vector2Add(gridToScreenPos(gridPosition), offset), atlasPosition);
}

void gui::RLIsoRenderer::drawTileLine(const Backend &be, Vec2 gridPosition, Vec2 mapSize)
{
    if (showOcean)
        drawAtlas(gridPosition + Vec2(-1, 1), {3, 8});
    while ((gridPosition.x >= 0 && gridPosition.x < mapSize.x)
        && (gridPosition.y >= 0 && gridPosition.y < mapSize.y)) {
        try {
            drawTile(be.getTile(gridPosition));
        } catch (Backend::BackendError &e) {}
        gridPosition.x++;
        gridPosition.y--;
    }
    if (showOcean)
        drawAtlas(gridPosition, {3, 8});
}

void gui::RLIsoRenderer::drawTile(const Tile &tile)
{
    drawAtlas(tile.pos, getRandomGroundTile(tile.pos));
    if (tile.pos == cursorPos && showHud)
        drawCursor();
    drawAtlas(tile.pos, getRandomTileDecor(tile.pos), groundOffset);
    for (Item item = Item::FOOD; item <= Item::THYSTAME && showItems; item = static_cast<Item>(static_cast<int>(item) + 1)) {
        if (tile.inventory[item] > 0) {
            drawItem(item, tile.pos);
        }
    }
    if (!tile.eggs.empty() && showEggs)
        drawEgg(tile.pos);
    for (const Player *player : tile.players)
        drawPlayer(*player);
}

void gui::RLIsoRenderer::drawItem(Item item, Vec2 gridPosition)
{
    Vec2 offsetI = {
        getRandomDeterministic(-atlasCellSize / 16, atlasCellSize / 16, static_cast<int>(item)),
        getRandomDeterministic(-atlasCellSize / 16, atlasCellSize / 16, static_cast<int>(item))
    };
    Vector2 offset = {static_cast<float>(offsetI.x), static_cast<float>(offsetI.y)};

    drawAtlas(gridPosition, getItemAtlasPos(item), Vector2Add(offset, groundOffset));
}

void gui::RLIsoRenderer::drawEgg(Vec2 gridPosition)
{
    drawAtlas(gridPosition, {10, 9}, groundOffset);
    drawAtlas(gridPosition, {4 + (animationCounter + hashVec(gridPosition)) % 6, 9}, groundOffset);
}

void gui::RLIsoRenderer::drawPlayer(const Player &player)
{
    Vec2 atlasPosition = {0, static_cast<int>(player.getLevel()) - 1};

    atlasPosition.x = static_cast<int>(player.getOrientation()) - 1;
    if (player.isElevating()) {
        atlasPosition.x += 8;
    } else if (player.isLaying()) {
        atlasPosition.x += 4;
    }
    drawShadow(player);
    drawAtlas(player.getPos(), atlasPosition, groundOffset);
}

void gui::RLIsoRenderer::drawShadow(const Player &player)
{
    Vec2 atlasPosition = {3, 9};

    if (player.isElevating())
        atlasPosition.y++;
    drawAtlas(player.getPos(), atlasPosition, groundOffset);
}

void gui::RLIsoRenderer::updateCursor(Vec2 mapSize)
{
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    Vec2 gridPos = screenPosToGrid(mouseWorldPos);

    cursorOnMap = gridPos.x >= 0 && gridPos.x < mapSize.x && gridPos.y >= 0 && gridPos.y < mapSize.y;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !hud.isPaused()) {
        if (cursorOnMap) {
            cursorPos = gridPos;
            cursorFixed = true;
        } else {
            cursorFixed = false;
        }   
    } else if (cursorOnMap && !cursorFixed)
        cursorPos = gridPos;
}

void gui::RLIsoRenderer::drawCursor()
{
    if ((!cursorOnMap && !cursorFixed) || hud.isPaused())
        return;
    drawAtlas(cursorPos, {4, 10});       
}

void gui::RLIsoRenderer::updateCamera(const Backend &be)
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
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) || IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
        camera.target = Vector2Add(camera.target, Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom));
    }
    if (IsKeyPressed(KEY_SPACE)) {
        centerCamera(be);
    } else if (be.getMapSize() != lastMapSize) {
        lastMapSize = be.getMapSize();
        centerCamera(be);
    }
}

void gui::RLIsoRenderer::centerCamera(const Backend &be)
{
    Vec2 mapSize = be.getMapSize();

    camera.target = gridToScreenPos({mapSize.x / 2, mapSize.y / 2});
    camera.zoom = mapSize.x > mapSize.y ? mapSize.x : mapSize.y;
    camera.offset = {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2)};
}

gui::Vec2 gui::RLIsoRenderer::getRandomGroundTile(Vec2 pos)
{
    Vec2 tilePos = {0, 8};
    int seed = hashVec(pos);
    int chance = getRandomDeterministic(0, 100, seed);

    if (chance < 10)
        tilePos.y += 2;
    else if (chance < 20)
        tilePos.y += 1;
    chance = getRandomDeterministic(0, 100, seed * 2 + seed);
    if (chance < 10)
        tilePos.x += 2;
    else if (chance < 20)
        tilePos.x += 1;
    return tilePos;
}

gui::Vec2 gui::RLIsoRenderer::getRandomTileDecor(Vec2 pos)
{
    Vec2 tilePos = {3, 11};
    int seed = hashVec(pos);
    int chance = getRandomDeterministic(0, 100, seed * 2);
    bool isRock = getRandomDeterministic(0, 100, seed) < 10;

    if (chance < 3 && !isRock)
        tilePos.x -= 3;
    else if (chance < 5)
        tilePos.x -= 2;
    else if (chance < 10 && !isRock)
        tilePos.x -= 1;
    return tilePos;
}

int gui::RLIsoRenderer::getRandomDeterministic(int min, int max, int seed)
{
    std::mt19937 gen(seed * initialSeed);

    return std::uniform_int_distribution<int>(min, max)(gen);
}

int gui::RLIsoRenderer::hashVec(Vec2 vec)
{
    return static_cast<int>(vec.x * 1000 + vec.y);
}
