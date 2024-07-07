/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"

gui::Player::Player(std::size_t id, Vec2 pos, Orientation orient, std::size_t level, std::size_t teamId)
    : id(id), pos(pos), orient(orient), level(level), teamId(teamId), elevating(false), laying(false) {}

std::string gui::Player::toString() const
{
    std::string str = "[";
    std::string elevStr = elevating ? "true" : "false";
    std::string layStr = laying ? "true" : "false";
    
    str += "id: " + std::to_string(id) + ", ";
    str += "pos: " + pos.toString() + ", ";
    str += "team: " + std::to_string(teamId) + ", ";
    str += "level: " + std::to_string(level) + ", ";
    str += "orientation: " + orientationToString(orient)  + ", ";
    str += "elevating: " + elevStr + ", ";
    str += "laying: " + layStr;
    str += "]";
    return str;
}

std::size_t gui::Player::getId() const
{
    return id;
}

gui::Player &gui::Player::setPos(Vec2 pos)
{
    this->pos = pos;
    return *this;
}

gui::Vec2 gui::Player::getPos() const
{
    return pos;
}

gui::Player &gui::Player::setTeam(std::size_t id)
{
    teamId = id;
    return *this;
}

std::size_t gui::Player::getTeam() const
{
    return teamId;
}

gui::Player &gui::Player::setLevel(std::size_t lvl)
{
    level = lvl;
    return *this;
}

gui::Orientation gui::Player::getOrientation() const
{
    return orient;
}

gui::Player &gui::Player::setOrientation(Orientation orientation)
{
    orient = orientation;
    return *this;
}

std::size_t gui::Player::getLevel() const
{
    return level;
}

gui::Player &gui::Player::setElevating(bool elevating)
{
    this->elevating = elevating;
    return *this;
}

bool gui::Player::isElevating() const
{
    return elevating;
}

gui::Player &gui::Player::setLaying(bool laying)
{
    this->laying = laying;
    return *this;
}

bool gui::Player::isLaying() const
{
    return laying;
}

std::ostream &gui::operator<<(std::ostream &out, const Player &player)
{
    return out << player.toString();
}
