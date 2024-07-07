/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile_handle
*/

#include <string.h>
#include "utils.h"
#include "server.h"
#include "tile.h"
#include "gui.h"

static void append_item(char **str, const char *name, list_t *list)
{
    size_t nb = 0;

    if (!str || !name || !list)
        return;
    nb = list_size(list);
    if (*str && strlen(*str) > 1 && nb > 0 && !strmcat(str, " ")) {
        *str = NULL;
        return;
    }
    while (nb > 0) {
        nb--;
        if (!strmcat(str, name) || (nb > 0 && !strmcat(str, " "))) {
            *str = NULL;
            return;
        }
    }
}

static void append_inventory(char **str, inventory_t *inv)
{
    char *inv_str = NULL;

    inv_str = inventory_to_string(inv);
    if (!inv_str) {
        free(*str);
        *str = NULL;
        return;
    }
    if (*str && *inv_str && strlen(*str) > 1 && strlen(inv_str) > 1
        && !strmcat(str, " ")) {
        free(inv_str);
        *str = NULL;
        return;
    }
    strmcat(str, inv_str);
    free(inv_str);
}

char *tile_to_string(tile_t *tile)
{
    char *str = NULL;

    if (!tile)
        return NULL;
    str = strdup("");
    append_item(&str, "player", &tile->players);
    append_item(&str, "egg", &tile->eggs);
    append_inventory(&str, &tile->inventory);
    return str;
}

static void apply_ejection(ejector_t *ejector, player_t *player)
{
    char buf[32];
    int dir_id = 0;

    if (player == ejector->emitter)
        return;
    memset(buf, 0, 32);
    world_move_player(ejector->server, player, ejector->new_pos);
    dir_id = world_get_direction(ejector->server, ejector->new_pos,
        ejector->emitter->position, player->direction);
    snprintf(buf, 32, "eject: %d", dir_id);
    nets_send(&ejector->server->net, player->sock, buf);
}

void tile_eject(server_t *server, player_t *emitter, tile_t *tile)
{
    ejector_t ejector = {0};
    vec2_t new_pos = {0};
    vec2_t wrapped_pos = {0};

    if (!server || !emitter || !tile)
        return;
    new_pos = vec2_add(emitter->position, emitter->direction);
    wrapped_pos = world_wrap_pos(new_pos, server->world.size);
    ejector = (ejector_t){server, emitter, wrapped_pos};
    list_apply(&tile->players, (applicator_t)apply_ejection, &ejector);
    world_remove_tile_eggs(server, tile);
    gui_broadcast_event(server, gui_send_expulsion, emitter);
}
