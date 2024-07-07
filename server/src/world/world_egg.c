/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_egg
*/

#include "server.h"
#include "utils.h"
#include "gui.h"
#include "tile.h"

static bool add_egg(server_t *server, egg_t *egg)
{
    tile_t *tile = NULL;

    if (!egg)
        return false;
    if (!list_add_ptr(&server->world.eggs, egg)) {
        free(egg);
        return false;
    }
    tile = world_get_tile(server, egg->position);
    if (!tile || !list_add_ptr(&tile->eggs, egg)) {
        list_remove_free(&server->world.eggs, -1);
        return false;
    }
    return true;
}

bool world_add_egg_from_player(server_t *server, player_t *player)
{
    egg_t *egg = NULL;

    if (!server || !player)
        return false;
    egg = egg_create_from_player(player);
    if (!egg)
        return false;
    gui_broadcast_event(server, gui_send_egg_lay_end, egg);
    return add_egg(server, egg);
}

bool world_add_egg_randomly(server_t *server, size_t team_id)
{
    if (!server)
        return false;
    return add_egg(server, egg_create_random(team_id, server->world.size));
}

static void apply_egg_deletion(server_t *server, egg_t *egg)
{
    if (egg->layer)
        gui_broadcast_event(server, gui_send_egg_death, egg);
    list_remove_if_free(&server->world.eggs, ptr_eq, egg);
}

bool world_remove_tile_eggs(server_t *server, tile_t *tile)
{
    if (!server || !tile)
        return false;
    list_apply(&tile->eggs, (applicator_t)apply_egg_deletion, server);
    list_clear(&tile->eggs, NULL);
    return TRUE_SLOG(server, DEBUG, "Eggs removed from tile (%d %d)",
        tile->position.x, tile->position.y);
}

static bool remove_from_world(server_t *server, egg_t *to_find)
{
    egg_t *egg = NULL;

    for (size_t i = 0; i < list_size(&server->world.eggs); i++) {
        egg = list_at(&server->world.eggs, i);
        if (egg == to_find && egg->layer)
            gui_broadcast_event(server, gui_send_egg_death, egg);
        if (egg == to_find) {
            return list_remove_free(&server->world.eggs, i);
        }
    }
    return false;
}

bool world_remove_egg(server_t *server, vec2_t pos, size_t team_id)
{
    tile_t *tile = NULL;
    egg_t *egg = NULL;

    tile = server ? world_get_tile(server, pos) : NULL;
    if (!server || !tile)
        return false;
    for (size_t i = 0; i < list_size(&tile->eggs); i++) {
        egg = list_at(&tile->eggs, i);
        if (egg->team_id == team_id) {
            list_remove(&tile->eggs, NULL, i);
            return remove_from_world(server, egg) && TRUE_SLOG(server, INFO,
                "Egg removed from tile (%d, %d)", pos.x, pos.y);
        }
    }
    return FALSE_SLOG(server, DEBUG, "No egg found at (%d %d) for team %ld",
        pos.x, pos.y, team_id);
}

static bool add_team_eggs(server_t *server, size_t team_id, size_t nb)
{
    for (size_t i = 0; i < nb; i++) {
        if (!world_add_egg_randomly(server, team_id))
            return false;
    }
    return true;
}

bool world_add_eggs_per_team(server_t *server, size_t nb)
{
    team_t *team = NULL;

    if (!server)
        return false;
    for (node_t *node = server->world.teams.head; node; node = node->next) {
        team = node->data;
        if (!add_team_eggs(server, team->id, nb))
            return FALSE_SLOG(server, CRITICAL,
                "Failed to add eggs for team %s", team->name);
    }
    return TRUE_SLOG(server, INFO, "Added %ld egg(s) per team", nb);
}
