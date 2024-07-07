/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Orientation
*/

#pragma once

#include <iostream>

namespace gui
{
    enum class Orientation
    {
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        LEFT = 4
    };
    std::string orientationToString(Orientation orientation);
    std::ostream &operator<<(std::ostream &out, const Orientation &orientation);
    Orientation operator-(const Orientation &orient, int nb);
}
