/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Vec2
*/

#pragma once

#include <iostream>

namespace gui
{
    struct Vec2
    {
        int x;
        int y;

        Vec2();
        Vec2(int x, int y);

        bool isPositive() const;
        std::string toString() const;
        bool operator==(const Vec2 &other) const;
        bool operator!=(const Vec2 &other) const;
        Vec2 operator+(const Vec2 &other) const;
        Vec2 operator-(const Vec2 &other) const;
        Vec2 operator*(const Vec2 &other) const;
        Vec2 operator/(const Vec2 &other) const;
        Vec2 &operator+=(const Vec2 &other);
        Vec2 &operator-=(const Vec2 &other);
        Vec2 &operator*=(const Vec2 &other);
        Vec2 &operator/=(const Vec2 &other);
    };
    std::ostream &operator<<(std::ostream &out, const Vec2 &vec);
}
