/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Inventory
*/

#pragma once

#include <iostream>
#include <vector>

namespace gui
{
    enum Item
    {
        FOOD = 0,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
    };

    struct Inventory
    {
        std::size_t food;
        std::size_t linemate;
        std::size_t deraumere;
        std::size_t sibur;
        std::size_t mendiane;
        std::size_t phiras;
        std::size_t thystame;

        Inventory();
        std::string toString() const;
        std::size_t &get(Item item);
        const std::size_t &get(Item item) const;
        std::size_t &operator[](Item item);
        const std::size_t &operator[](Item item) const;
        void increment(Item item);
        void decrement(Item item);
    };
    std::ostream &operator<<(std::ostream &out, const Inventory &inv);
    std::string to_string(Item item);
}
