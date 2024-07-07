/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IRLRenderer
*/

#pragma once

#include "Backend.hpp"

namespace gui
{
    class IRLRenderer
    {
        public:
            IRLRenderer() = default;
            virtual std::string getName() const = 0;
            virtual void update(const Backend &be) = 0;
            virtual void render(const Backend &be) = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
    };
}
