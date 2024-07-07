/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_print
*/

#include <ncurses.h>
#include "inventory.h"

void inventory_print(inventory_t *inv)
{
    if (!inv)
        return;
    printw(
        "[food: %ld, lmt: %ld, drm: %ld, "
        "sbr: %ld, mdn: %ld, phr: %ld, ths: %ld]\n",
        inv->food, inv->linemate, inv->deraumere, inv->sibur,
        inv->mendiane, inv->phiras, inv->thystame
    );
}
