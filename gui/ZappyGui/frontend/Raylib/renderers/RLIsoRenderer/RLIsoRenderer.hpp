/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLIsoRenderer
*/

#pragma once

#include <filesystem>
#include <random>
#include "IRLRenderer.hpp"
#include "RLGraphics.hpp"
#include "RLAtlas.hpp"
#include "RLIsoHudRenderer.hpp"
#include "RLMusic.hpp"

namespace gui
{
    class RLIsoRenderer: public IRLRenderer
    {
        const Color backgroundColor = {38, 128, 208, 255};
        const float animationFrameTime = 0.15f;
        const int atlasCellSize = 32;
        const Vector2 groundOffset = {0, -7};
        const std::vector<std::filesystem::path> atlasPath = {
            "gui/assets/raylib/atlas/RLISO-atlas.png",
            "assets/raylib/atlas/RLISO-atlas.png",
        };
        const std::vector<std::filesystem::path> musicPath = {
            "gui/assets/raylib/RLISO-bg.mp3",
            "assets/raylib/RLISO-bg.mp3",
        };

        RLAtlas atlas;
        RLMusic music;
        RLIsoHudRenderer hud;
        int animationCounter = 0;
        double animationClock = 0;
        Camera2D camera = {0};
        bool draggingCamera = false;
        Vec2 lastMapSize = {0, 0};
        float minZoom = 0.7f;
        float maxZoom = 5.0f;
        long initialSeed = 0;
        bool showOcean = true;
        bool showItems = true;
        bool showEggs = true;
        Vec2 cursorPos;
        bool cursorFixed = false;
        bool cursorOnMap = false;
        bool showHud = true;

        public:
            RLIsoRenderer();
            std::string getName() const override;
            void update(const Backend &be) override;
            void render(const Backend &be) override;
            void start() override;
            void stop() override;

            RLAtlas &getAtlas();
            RLMusic &getMusic();
            bool tileSelected() const;
            bool tileSelected(Vec2 &buf) const;
            void drawTile(const Tile &tile, Vector2 position, Vector2 scale = {1, 1});
            void drawItem(Item item, Vector2 position, Vector2 scale = {1, 1}, bool tileRender = false);
            void drawPlayer(const Player &player, Vector2 position, Vector2 scale = {1, 1});
            Vec2 getItemAtlasPos(Item item) const;
            bool getShowOcean() const;
            void setShowOcean(bool showOcean);
            bool getShowItems() const;
            void setShowItems(bool showItems);
            bool getShowEggs() const;
            void setShowEggs(bool showEggs);

            NEW_ERROR(RLIsoRendererError);

        private:
            Vector2 gridToScreenPos(Vec2 gridPosition) const;
            Vec2 screenPosToGrid(Vector2 ScreenPosition) const;
            void drawAtlas(Vec2 gridPosition, Vec2 atlasPosition, Vector2 offset = {0, 0});
            void drawTileLine(const Backend &be, Vec2 gridPosition, Vec2 mapSize);
            void drawTile(const Tile &tile);
            void drawItem(Item item, Vec2 gridPosition);
            void drawEgg(Vec2 gridPosition);
            void drawPlayer(const Player &player);
            void drawShadow(const Player &player);
            void drawCursor();
            void updateCursor(Vec2 mapSize);

            void updateCamera(const Backend &be);
            void centerCamera(const Backend &be);
            
            Vec2 getRandomGroundTile(Vec2 pos);
            Vec2 getRandomTileDecor(Vec2 pos);
            int getRandomDeterministic(int min, int max, int seed);
            static int hashVec(Vec2 vec);
    };
}
