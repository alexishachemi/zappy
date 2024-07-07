/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#pragma once

#include <vector>
#include "Inventory.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include "error.hpp"

namespace gui
{
    class Tile
    {
        public:
            const Vec2 pos;
            Inventory inventory;
            std::vector<Player*> players;
            std::vector<Egg*> eggs;

            Tile(Vec2 pos);

            Player &getPlayer(std::size_t id);
            void addPlayer(Player &player);
            void removePlayer(std::size_t id);
            void movePlayer(Player &player, Tile &to);
            void addEgg(Egg &egg);
            void removeEgg(std::size_t id);
            void clearEggs();

            Tile &operator=(const Tile &tile);
        
            NEW_ERROR(TileError)
    };
}
