/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RL2DRenderer
*/

#pragma once

#include <filesystem>
#include "IRLRenderer.hpp"
#include "RLGraphics.hpp"
#include "RLAtlas.hpp"
#include "RLMusic.hpp"

namespace gui
{
    class RL2DRenderer: public IRLRenderer
    {
        const Color backgroundColor = {25, 118, 157, 255};
        const float animationFrameTime = 0.15f;
        const int atlasCellSize = 64;
        const std::vector<std::filesystem::path> atlasPath = {
            "gui/assets/raylib/atlas/RL2D-atlas.png",
            "assets/raylib/atlas/RL2D-atlas.png",
        };
        const std::vector<std::filesystem::path> musicPath = {
            "gui/assets/raylib/RL2D-bg.mp3",
            "assets/raylib/RL2D-bg.mp3",
        };

        RLAtlas atlas;
        RLMusic music;
        int animationCounter = 0;
        double animationClock = 0;
        Camera2D camera = {0};
        bool draggingCamera = false;
        Vec2 lastMapSize = {0, 0};
        float minZoom = 0.7f;
        float maxZoom = 5.0f;
        long randomSeed = 0;

        public:
            RL2DRenderer();
            std::string getName() const override;
            void update(const Backend &be) override;
            void render(const Backend &be) override;
            void start() override;
            void stop() override;

            NEW_ERROR(RL2DRendererError);

        private:
            void drawAtlas(Vec2 gridPosition, Vec2 atlasPosition, Vector2 offset = {0, 0});
            void drawTile(const Tile &tile, Vec2 mapSize);
            void drawPlayer(const Player &player);
            void drawItem(Item item, Vec2 gridPosition);
            void drawEgg(Vec2 gridPosition);
            Vector2 gridToScreenPos(Vec2 gridPosition) const;
            void updateCamera(const Backend &be);
            void centerCamera(const Backend &be);
            void drawGroundCliff(Vec2 mapSize);
            static Vec2 getGroundTilePos(Vec2 tilePosition, Vec2 mapSize);
            static Vec2 getSingleTilePos();
            static Vec2 getSlimHTilePos(Vec2 tilePosition, Vec2 mapSize);
            static Vec2 getSlimVTilePos(Vec2 tilePosition, Vec2 mapSize);
            static int getRandomDeterministic(int min, int max, int seed);
    };
}
