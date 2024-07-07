/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#pragma once

#include "Vec2.hpp"

namespace gui
{
    class Egg
    {
        public:
            Egg(std::size_t id, Vec2 pos, int teamId);

            std::string toString() const;
            std::size_t getId() const;
            Egg &setPos(Vec2 pos);
            Vec2 getPos() const;
            Egg &setTeam(int id);
            int getTeam() const;
        
        private:
            std::size_t id;
            Vec2 pos;
            int teamId;
    };
    std::ostream &operator<<(std::ostream &out, const Egg &egg);
}
