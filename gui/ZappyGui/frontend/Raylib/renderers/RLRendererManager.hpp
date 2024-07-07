/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLRendererManager
*/

#pragma once

#include <vector>
#include <memory>
#include "IRLRenderer.hpp"
#include "error.h"

namespace gui
{
    class RLRendererManager
    {
        std::vector<std::unique_ptr<IRLRenderer>> renderers;
        std::vector<std::unique_ptr<IRLRenderer>> hudRenderers;
        IRLRenderer *currentRenderer = nullptr;

        public:
            void init();

            void addRenderer(IRLRenderer *renderer);
            IRLRenderer *getRenderer(const std::string &name);
            IRLRenderer *getRenderer();
            void setCurrentRenderer(const std::string &name);
            void nextRenderer();
            void previousRenderer();

            NEW_ERROR(RLRendererManagerError);
    };
}
