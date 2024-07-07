/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#include "Egg.hpp"

gui::Egg::Egg(std::size_t id, Vec2 pos, int teamId)
    : id(id), pos(pos), teamId(teamId) {}

std::string gui::Egg::toString() const
{
    std::string str = "[";

    str += "id: " + std::to_string(id) + ", ";
    str += "pos: " + pos.toString() + ", ";
    str += "teamId: " + std::to_string(teamId);
    str += "]";
    return str;
}

std::size_t gui::Egg::getId() const
{
    return id;
}

gui::Egg &gui::Egg::setPos(Vec2 pos)
{
    this->pos = pos;
    return *this;
}

gui::Vec2 gui::Egg::getPos() const
{
    return pos;
}

gui::Egg &gui::Egg::setTeam(int id)
{
    this->teamId = id;
    return *this;
}

int gui::Egg::getTeam() const
{
    return teamId;
}

std::ostream &gui::operator<<(std::ostream &out, const Egg &egg)
{
    return out << egg.toString();
}
