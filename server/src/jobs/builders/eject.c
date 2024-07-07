/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include "server.h"
#include "utils.h"

static void eject(server_t *server, player_t *player,
    UNUSED const char *arg, void *data)
{
    tile_eject(server, player, (tile_t *)data);
    nets_send(&server->net, player->sock, "ok");
}

static void eject_fail(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    nets_send(&server->net, player->sock, "ko");
}

static bool can_eject(UNUSED server_t *server, UNUSED player_t *player,
    UNUSED const char *arg, void *data)
{
    tile_t *tile = data;

    return list_size(&tile->players) > 1 || list_size(&tile->eggs) > 0;
}

bool job_build_eject(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = world_get_tile(server, player->position);
    jdata->check = can_eject;
    jdata->failure = eject_fail;
    jdata->sucess = eject;
    return jdata->data != NULL;
}
