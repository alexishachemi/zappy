/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Inventory
*/

#include "Inventory.hpp"

gui::Inventory::Inventory()
    : food(0), linemate(0), deraumere(0), sibur(0), mendiane(0), phiras(0), thystame(0) {}

std::string gui::Inventory::toString() const
{
    std::string str = "[";

    str += "food " + std::to_string(food);
    str += ", linemate " + std::to_string(linemate);
    str += ", deraumere " + std::to_string(deraumere);
    str += ", sibur " + std::to_string(sibur);
    str += ", mendiane " + std::to_string(mendiane);
    str += ", phiras " + std::to_string(phiras);
    str += ", thystame " + std::to_string(thystame);
    str += "]";
    return str;
}

std::size_t &gui::Inventory::get(Item item)
{
    switch (item) {
        case Item::LINEMATE:
            return linemate;
        case Item::DERAUMERE:
            return deraumere;
        case Item::SIBUR:
            return sibur;
        case Item::MENDIANE:
            return mendiane;
        case Item::PHIRAS:
            return phiras;
        case Item::THYSTAME:
            return thystame;
        default:
            return food;
    }
}

const std::size_t &gui::Inventory::get(Item item) const
{
    switch (item) {
        case Item::LINEMATE:
            return linemate;
        case Item::DERAUMERE:
            return deraumere;
        case Item::SIBUR:
            return sibur;
        case Item::MENDIANE:
            return mendiane;
        case Item::PHIRAS:
            return phiras;
        case Item::THYSTAME:
            return thystame;
        default:
            return food;
    }
}

std::size_t &gui::Inventory::operator[](Item item)
{
    return get(item);
}

const std::size_t &gui::Inventory::operator[](Item item) const
{
    return get(item);
}

void gui::Inventory::increment(Item item)
{
    get(item)++;
}

void gui::Inventory::decrement(Item item)
{
    std::size_t &i = get(item);

    if (i > 0)
        i--;
}

std::ostream &gui::operator<<(std::ostream &out, const Inventory &inv)
{
    return out << inv.toString();
}

std::string gui::to_string(Item item)
{
    switch (item) {
        case Item::FOOD:
            return "food";
        case Item::LINEMATE:
            return "linemate";
        case Item::DERAUMERE:
            return "deraumere";
        case Item::SIBUR:
            return "sibur";
        case Item::MENDIANE:
            return "mendiane";
        case Item::PHIRAS:
            return "phiras";
        case Item::THYSTAME:
            return "thystame";
        default:
            return "unknown";
    }
}
