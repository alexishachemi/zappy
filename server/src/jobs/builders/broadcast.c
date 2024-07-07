/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "server.h"
#include "utils.h"

static void broadcast(server_t *server, player_t *player,
    const char *arg, UNUSED void *data)
{
    server_broadcast(server, player, arg);
    nets_send(&server->net, player->sock, "ok");
}

bool job_build_broadcast(server_t *server, player_t *player,
    job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = broadcast;
    return true;
}
