/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_get
*/

#include "server.h"

vec2_t world_wrap_pos(vec2_t pos, vec2_t size)
{
    while (pos.x < 0)
        pos.x += size.x;
    while (pos.y < 0)
        pos.y += size.y;
    pos.x = pos.x % size.x;
    pos.y = pos.y % size.y;
    return pos;
}

tile_t *world_get_tile(server_t *server, vec2_t pos)
{
    if (!server || !server->world.map)
        return NULL;
    pos = world_wrap_pos(pos, server->world.size);
    return server->world.map[pos.y] + pos.x;
}

tile_t *world_get_random_tile(server_t *server, vec2_t *pos_buf)
{
    vec2_t pos = {0};
    world_t *world = NULL;

    if (!server)
        return NULL;
    world = &server->world;
    pos = (vec2_t){rand() % world->size.x, rand() % world->size.y};
    if (pos_buf)
        *pos_buf = pos;
    return world_get_tile(server, pos);
}
