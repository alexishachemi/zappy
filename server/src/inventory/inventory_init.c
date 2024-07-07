/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_init
*/

#include <string.h>
#include "inventory.h"

void inventory_init(inventory_t *inv)
{
    if (!inv)
        return;
    memset(inv, 0, sizeof(inventory_t));
}
