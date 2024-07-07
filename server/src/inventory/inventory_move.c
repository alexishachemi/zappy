/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_move
*/

#include "inventory.h"

bool inventory_move(inventory_t *from, inventory_t *to,
    const char *name, size_t amount)
{
    size_t *from_item = NULL;
    size_t *to_item = NULL;

    if (!from || !to || !name)
        return false;
    if (amount == 0)
        return true;
    from_item = inventory_index(from, name);
    to_item = inventory_index(to, name);
    if (!from_item || !to_item || *from_item < amount)
        return false;
    *from_item -= amount;
    *to_item += amount;
    return true;
}
