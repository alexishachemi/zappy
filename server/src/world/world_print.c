/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_print
*/

#include <stdio.h>
#include <ncurses.h>
#include "server.h"

static void print_tile(tile_t *tile)
{
    char c = '*';
    inventory_t *inv = &tile->inventory;

    if (inv->food > 0)
        c = 'F';
    if (inv->deraumere > 0 || inv->linemate > 0 || inv->mendiane > 0 ||
        inv->phiras > 0 || inv->sibur > 0 || inv->thystame > 0)
        c = 'S';
    if (!list_empty(&tile->eggs))
        c = 'E';
    if (!list_empty(&tile->players))
        c = 'P';
    putchar(c);
}

void world_print_map(server_t *server)
{
    if (!server || !server->world.map)
        return;
    for (int y = 0; y < server->world.size.y; y++) {
        for (int x = 0; x < server->world.size.x; x++) {
            print_tile(server->world.map[y] + x);
        }
        printf("\n");
    }
}
