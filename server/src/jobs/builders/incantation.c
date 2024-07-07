/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include <string.h>
#include "server.h"
#include "utils.h"
#include "gui.h"

static void incantation(server_t *server, player_t *player,
    UNUSED const char *arg, void *data)
{
    player_elevate(server, player);
    tile_remove_elev_ressources((tile_t *)data, player->level);
}

static void incantation_fail(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    player_cancel_elevation(server, player);
}

static void apply_incantation_start(server_t *server, player_t *player)
{
    nets_send(&server->net, player->sock, "Elevation underway");
}

static void incantation_start(server_t *server, player_t *player,
    UNUSED const char *arg, void *data)
{
    player_setup_elevation(server, player, (tile_t *)data);
    apply_incantation_start(server, player);
    list_apply(&player->elevation_list,
        (applicator_t)apply_incantation_start, server);
}

static bool can_elevate(UNUSED server_t *server, player_t *player,
    UNUSED const char *arg, void *data)
{
    return tile_can_elevate((tile_t *)data, player);
}

bool job_build_incantation(server_t *server, player_t *player,
    job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->check_first = true;
    jdata->data = world_get_tile(server, player->position);
    jdata->check = can_elevate;
    jdata->start = incantation_start;
    jdata->failure = incantation_fail;
    jdata->sucess = incantation;
    return jdata->data != NULL;
}
