/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IGraphics
*/

#pragma once

#include "Backend.hpp"

namespace gui
{
    class IGraphics
    {
        public:
            virtual ~IGraphics() = default;
            virtual bool update(const Backend &be) = 0;
    };
}
