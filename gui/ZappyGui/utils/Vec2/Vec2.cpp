/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Vec2
*/

#include "Vec2.hpp"

gui::Vec2::Vec2()
    : x(0)
    , y(0)
{
}

gui::Vec2::Vec2(int x, int y)
    : x(x)
    , y(y)
{
}

bool gui::Vec2::isPositive() const
{
    return x >= 0 && y >= 0;
}

std::string gui::Vec2::toString() const
{
    return std::to_string(x) + " " + std::to_string(y);
}

bool gui::Vec2::operator==(const Vec2 &other) const
{
    return x == other.x && y == other.y;
}

bool gui::Vec2::operator!=(const Vec2 &other) const
{
    return !(*this == other);
}

gui::Vec2 gui::Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

gui::Vec2 gui::Vec2::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}

gui::Vec2 gui::Vec2::operator*(const Vec2 &other) const
{
    return Vec2(x * other.x, y * other.y);
}

gui::Vec2 gui::Vec2::operator/(const Vec2 &other) const
{
    return Vec2(x / other.x, y / other.y);
}

gui::Vec2 &gui::Vec2::operator+=(const Vec2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

gui::Vec2 &gui::Vec2::operator-=(const Vec2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

gui::Vec2 &gui::Vec2::operator*=(const Vec2 &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

gui::Vec2 &gui::Vec2::operator/=(const Vec2 &other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

std::ostream &gui::operator<<(std::ostream &out, const Vec2 &vec)
{
    return out << vec.toString();
}
