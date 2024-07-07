/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile_init
*/

#include "tile.h"

void tile_init(tile_t *tile, vec2_t position)
{
    if (!tile)
        return;
    list_init(&tile->players);
    list_init(&tile->eggs);
    inventory_init(&tile->inventory);
    tile->position = position;
}

void tile_deinit(tile_t *tile)
{
    if (!tile)
        return;
    list_clear(&tile->players, NULL);
    list_clear(&tile->eggs, NULL);
}
