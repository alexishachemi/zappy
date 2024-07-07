/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_init
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static void free_map(tile_t **map, vec2_t size)
{
    if (!map)
        return;
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            tile_deinit(map[y] + x);
        }
        free(map[y]);
    }
    free(map);
}

static tile_t **create_map(vec2_t size)
{
    tile_t **map = NULL;
    size_t y = 0;

    if (!(size.x > 0 && size.y > 0))
        return NULL;
    map = malloc(sizeof(tile_t *) * size.y);
    if (!map)
        return NULL;
    for (int i = 0; i < size.y; i++) {
        map[i] = malloc(sizeof(tile_t) * size.x);
        if (!map[i]) {
            free_map(map, (vec2_t){size.x, y});
            return NULL;
        }
        for (int j = 0; j < size.x; j++) {
            tile_init(map[i] + j, (vec2_t){j, y});
        }
        y++;
    }
    return map;
}

bool world_init(server_t *server, vec2_t size, const item_density_list_t map)
{
    world_t *world = NULL;

    if (!server)
        return false;
    world = &server->world;
    world->size = size;
    world->freq = 100;
    world->spawn_timer = 0;
    list_init(&world->teams);
    list_init(&world->players);
    list_init(&world->eggs);
    world->map = create_map(size);
    if (!world_set_items_density(server, map)) {
        world_deinit(server);
        return false;
    }
    return world->map != NULL;
}

void world_deinit(server_t *server)
{
    if (!server)
        return;
    list_clear_free(&server->world.players);
    list_clear_free(&server->world.eggs);
    list_clear(&server->world.teams, (callback_t)team_destroy);
    free_map(server->world.map, server->world.size);
    server->world.map = NULL;
}
