/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLGraphics
*/

#pragma once

#include <filesystem>
#include "raylib.h"
#include "IGraphics.hpp"
#include "RLRendererManager.hpp"

namespace gui
{
    class RLGraphics: public IGraphics
    {
        static const unsigned int maxFps;
        static const Vector2 screenSize;
        static const ConfigFlags configFlags;

        int animationCounter;
        float animationClock;
        RLRendererManager rendererManager;

        public:
            RLGraphics();
            ~RLGraphics();
            bool update(const Backend &be) override;

        private:
            void handleKeyboardInput(const Backend &be);
    };
}
