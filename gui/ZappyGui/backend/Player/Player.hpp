/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#pragma once

#include "Inventory.hpp"
#include "Orientation.hpp"
#include "Vec2.hpp"

namespace gui
{
    class Player
    {
        public:
            Inventory inventory;

            Player(std::size_t id, Vec2 pos = {0, 0}, Orientation orient = Orientation::UP, std::size_t level = 1, std::size_t teamId = 0);

            std::string toString() const;
            std::size_t getId() const;
            Player &setPos(Vec2 pos);
            Vec2 getPos() const;
            Player &setTeam(std::size_t id);
            std::size_t getTeam() const;
            Player &setLevel(std::size_t lvl);
            Orientation getOrientation() const;
            Player &setOrientation(Orientation orientation);
            std::size_t getLevel() const;
            Player &setElevating(bool elevating);
            bool isElevating() const;
            Player &setLaying(bool laying);
            bool isLaying() const;

        private:
            std::size_t id;
            Vec2 pos;
            Orientation orient;
            std::size_t level;
            std::size_t teamId;
            bool elevating;
            bool laying;
    };
    std::ostream &operator<<(std::ostream &out, const Player &player);
}
