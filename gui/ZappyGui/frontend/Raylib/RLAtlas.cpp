/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLAtlas
*/

#include "RLAtlas.hpp"

gui::RLAtlas::~RLAtlas()
{
    unload();
}

bool gui::RLAtlas::load(const std::filesystem::path &path, unsigned int cellSize)
{
    if (!std::filesystem::exists(path))
        return false;
    unload();
    texture = LoadTexture(path.c_str());
    if (texture.id == 0)
        return false;
    this->cellSize = cellSize;
    loaded = true;
    return true;
}

bool gui::RLAtlas::load(const std::vector<std::filesystem::path> &path, unsigned int cellSize)
{
    for (auto &p : path) {
        if (load(p, cellSize))
            return true;
    }
    return false;
}

void gui::RLAtlas::unload()
{
    if (!loaded) {
        return;
    }
    UnloadTexture(texture);
    loaded = false;
}

void gui::RLAtlas::draw(Vector2 screenPosition, Vec2 atlasPosition, Vector2 scale, Vector2 offset)
{
    Rectangle drawRect = {
        static_cast<float>(atlasPosition.x * cellSize),
        static_cast<float>(atlasPosition.y * cellSize),
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    };
    Rectangle destRect = {
        screenPosition.x + (offset.x * scale.x),
        screenPosition.y + (offset.y * scale.y),
        cellSize * scale.x,
        cellSize * scale.y
    };
    DrawTexturePro(texture, drawRect, destRect, {0, 0}, 0, WHITE);
}

int gui::RLAtlas::getCellSize() const
{
    return cellSize;
}

bool gui::RLAtlas::isLoaded() const
{
    return loaded;
}
