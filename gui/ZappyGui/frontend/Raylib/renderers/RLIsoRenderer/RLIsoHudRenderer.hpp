/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLIsoRenderer
*/

#pragma once

#include <filesystem>
#include <vector>
#include "raylib.h"
#include "error.hpp"
#include "Backend.hpp"

namespace gui
{
    class RLIsoRenderer;

    class RLIsoHudRenderer
    {
        const int sideBarSpeed = 20;
        const float sideBarMoveTime = 0.000001f;
        const std::vector<std::filesystem::path> stylePath = {
            "gui/assets/raylib/gui_style.rgs",
            "assets/raylib/gui_style.rgs",
        };

        bool loaded = false;
        const Tile *selectedTile = nullptr;
        float sideBarCurrentX = -1000;
        float sideBarClock = 0;
        float renderScaleF = 1;
        Vector2 renderScale = {1, 1};
        bool showSettings = false;
        float volume = 0.3f;

        public:
            RLIsoHudRenderer();
            void update(const Backend &be, RLIsoRenderer &renderer);
            void render(const Backend &be, RLIsoRenderer &renderer);
            bool isPaused() const;

            NEW_ERROR(RLIsoHudRendererError);
    
        private:
            int getSideBarHiddenX() const;
            int getSideBarShownX() const;
            void drawSideBar(const Backend &be, RLIsoRenderer &renderer, Vector2 position);
            void drawSettingsButton(const Backend &be, RLIsoRenderer &renderer);
            void drawSettings(const Backend &be, RLIsoRenderer &renderer);
            void drawToggles(const Backend &be, RLIsoRenderer &renderer, Rectangle rect);
            void drawSliders(const Backend &be, RLIsoRenderer &renderer, Rectangle rect);
    };
}