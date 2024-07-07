/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLAtlas
*/

#pragma once

#include <filesystem>
#include <vector>
#include "raylib.h"
#include "error.hpp"
#include "Vec2.hpp"

namespace gui
{
    class RLAtlas
    {
        bool loaded = false;
        Texture2D texture;
        unsigned int cellSize;

        public:
            ~RLAtlas();
            bool load(const std::filesystem::path &path, unsigned int cellSize);
            bool load(const std::vector<std::filesystem::path> &path, unsigned int cellSize);
            void unload();
            void draw(Vector2 screenPosition, Vec2 atlasPosition, Vector2 scale = {1, 1}, Vector2 offset = {0, 0});
            int getCellSize() const;
            bool isLoaded() const;

            NEW_ERROR(RLAtlasError);
    };
}