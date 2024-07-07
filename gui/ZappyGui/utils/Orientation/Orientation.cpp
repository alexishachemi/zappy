/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Orientation
*/

#include "Orientation.hpp"

std::string gui::orientationToString(Orientation orientation)
{
    switch (orientation) {
        case Orientation::UP:
            return "UP";
        case Orientation::RIGHT:
            return "RIGHT";
        case Orientation::DOWN:
            return "DOWN";
        case Orientation::LEFT:
            return "LEFT";
    }
    return "";
}

std::ostream &gui::operator<<(std::ostream &out, const Orientation &orientation)
{
    return out << orientationToString(orientation);
}

gui::Orientation gui::operator-(const Orientation &orient, int nb)
{
    return static_cast<Orientation>(static_cast<int>(orient) - nb);
}
