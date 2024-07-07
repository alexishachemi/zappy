/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_directions
*/

#include "server.h"

static vec2_t get_dir(vec2_t map_size, vec2_t to, vec2_t from)
{
    vec2_t dir;
    vec2_t d = {to.x - from.x, to.y - from.y};
    vec2_t w = {map_size.x - abs(d.x), map_size.y - abs(d.y)};

    if (abs(d.x) < w.x)
        dir.x = d.x;
    else
        dir.x = d.x > 0 ? -w.x : w.x;
    if (abs(d.y) < w.y)
        dir.y = d.y;
    else
        dir.y = d.y > 0 ? -w.y : w.y;
    dir.x = dir.x != 0 ? dir.x / abs(dir.x) : dir.x;
    dir.y = dir.y != 0 ? dir.y / abs(dir.y) : dir.y;
    return dir;
}

static int get_dir_id(vec2_t dir, vec2_t up)
{
    return vec2_rotate_id(vec2_direction_to_id(dir), VEC2_UP, up);
}

int world_get_direction(server_t *server, vec2_t from, vec2_t to, vec2_t up)
{
    return get_dir_id(get_dir(server->world.size, to, from), up);
}
