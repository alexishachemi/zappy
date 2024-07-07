/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_ressources
*/

#include <string.h>
#include "world.h"
#include "gui.h"
#include "utils.h"

static const item_density_list_t default_densities = {
    {FOOD, 0.5},
    {LINEMATE, 0.3},
    {DERAUMERE, 0.15},
    {SIBUR, 0.1},
    {MENDIANE, 0.1},
    {PHIRAS, 0.08},
    {THYSTAME, 0.05},
};

inventory_t world_count_items(const server_t *server)
{
    inventory_t count = {0};
    tile_t *tile = NULL;

    if (!server || !server->world.map)
        return count;
    for (int y = 0; y < server->world.size.y; y++) {
        for (int x = 0; x < server->world.size.x; x++) {
            tile = server->world.map[y] + x;
            inventory_add(&count, &tile->inventory);
        }
    }
    return count;
}

static tile_t *get_tile(server_t *server, list_t *tiles_buf)
{
    tile_t *tile = NULL;
    vec2_t pos_buf = {0};
    vec2_t *pos_ptr = NULL;

    tile = world_get_random_tile(server, &pos_buf);
    if (!tile)
        return NULL;
    if (tiles_buf && !list_find_if(tiles_buf, vec2_ptr_eq, &pos_buf)) {
        pos_ptr = list_add(tiles_buf, alloc_vec2);
        if (!pos_ptr)
            return NULL;
        memcpy(pos_ptr, &pos_buf, sizeof(vec2_t));
    }
    return tile;
}

bool world_spawn_item(server_t *server, item_t item, size_t nb,
    list_t *tiles_buf)
{
    tile_t *tile = NULL;
    size_t *items = NULL;

    if (nb)
        SLOG(server, DEBUG, "Spawning %ld %s", nb, item_to_string(item));
    while (nb > 0) {
        tile = get_tile(server, tiles_buf);
        if (!tile)
            return false;
        items = inventory_index_item(&tile->inventory, item);
        if (!items)
            return false;
        *items += 1;
        nb--;
    }
    return true;
}

static void apply_broadcast_tiles(server_t *server, vec2_t *pos)
{
    gui_broadcast_event(server, gui_send_tile_info, pos);
}

bool world_spawn_ressources(server_t *server)
{
    inventory_t desired = {0};
    inventory_t current = {0};
    list_t spawned_pos = {0};

    if (!server)
        return false;
    list_init(&spawned_pos);
    desired = server->world.spawn_map;
    current = world_count_items(server);
    inventory_sub(&desired, &current);
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        if (!world_spawn_item(server, i,
            *inventory_index_item(&desired, i), &spawned_pos))
            return false;
    }
    list_apply(&spawned_pos, (applicator_t)apply_broadcast_tiles, server);
    list_clear_free(&spawned_pos);
    return true;
}

bool world_set_item_density(server_t *server, item_t item, float density)
{
    size_t *items = NULL;

    if (!server)
        return false;
    items = inventory_index_item(&server->world.spawn_map, item);
    if (!items)
        return false;
    *items = server->world.size.x * server->world.size.y * density;
    return true;
}

bool world_set_items_density(server_t *server, const item_density_list_t map)
{
    if (!server)
        return false;
    if (!map)
        map = default_densities;
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        if (!world_set_item_density(server, map[i].item, map[i].density))
            return false;
    }
    return true;
}
